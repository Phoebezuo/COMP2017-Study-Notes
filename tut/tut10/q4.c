#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>

#define WIDTH 512
#define NTHREADS 4
#define CHUNK (WIDTH / NTHREADS)
#define IDX(x, y) ((y) * WIDTH + (x))

typedef struct {
	size_t id;
	float* result;
	const float* a;
	const float* b;
} worker_args;

void* worker_multiply(void* args) {

	worker_args* wargs = (worker_args*) args;

	const size_t start = wargs->id * CHUNK;
	const size_t end = wargs->id == NTHREADS - 1 ? WIDTH : (wargs->id + 1) * CHUNK;

	for (size_t i = start; i < end; i++) {
		for (size_t j = 0; j < WIDTH; j++) {
			for (size_t k = 0; k < WIDTH; k++) {
				wargs->result[IDX(j, i)] += wargs->a[IDX(k, i)] * wargs->b[IDX(j, k)];
			}
		}
	}

	return NULL;
}

/**
 * Returns the matrix multiplication of a and b.
 */
float* multiply(const float* a, const float* b) {

	float* result = calloc(WIDTH * WIDTH, sizeof(float));

	worker_args args[NTHREADS];
	pthread_t thread_ids[NTHREADS];

	for (size_t i = 0; i < NTHREADS; i++) {
		args[i] = (worker_args) {
			.a = a,
			.b = b,
			.id = i,
			.result = result,
		};
	}

	// Launch threads
	for (size_t i = 0; i < NTHREADS; i++) {
		pthread_create(thread_ids + i, NULL, worker_multiply, args + i);
	}

	// Wait for threads to finish
	for (size_t i = 0; i < NTHREADS; i++) {
		pthread_join(thread_ids[i], NULL);
	}

	return result;
}

/**
 * Returns a Hadamard matrix, if H is Hadamard matrix, then
 * HH^T = nI, where I is the identity matrix and n is the width.
 * Easy to verify that the matrix multiplication was done correctly.
 *
 * Sylvester's construction implemented here only works
 * for matrices that have width that is a power of 2.
 *
 * Note that this construction produces matrices that are symmetric.
 */
float* hadamard(void) {

	// Ensure the width is a power of 2
	assert(((WIDTH - 1) & WIDTH) == 0);

	size_t w = WIDTH;
	size_t quad_size = 1;

	float* result = malloc(WIDTH * WIDTH * sizeof(float));

	result[0] = 1;
	while ((w >>= 1) != 0) {
		// Duplicate the upper left quadrant into the other three quadrants
		for (size_t y = 0; y < quad_size; ++y) {
			for (size_t x = 0; x < quad_size; ++x) {
				const float v = result[IDX(x, y)];
				result[IDX(x + quad_size, y)] = v;
				result[IDX(x, y + quad_size)] = v;
				result[IDX(x + quad_size, y + quad_size)] = -v;
			}
		}

		quad_size *= 2;
	}

	return result;
}

// Displays a matrix.
void display(const float* matrix) {

	for (size_t y = 0; y < WIDTH; y++) {
		for (size_t x = 0; x < WIDTH; x++) {
			printf("%6.2f ", matrix[IDX(x, y)]);
		}
		printf("\n");
	}
}

int main(void) {

	// Construct the matrices
	float* a = hadamard();
	float* b = hadamard();

	// Compute the result
	float* r = multiply(a, b);

	// Verify the result
	for (size_t y = 0; y < WIDTH; y++) {
		for (size_t x = 0; x < WIDTH; x++) {
			assert(x == y ? r[IDX(x, y)] == WIDTH : r[IDX(x, y)] == 0);
		}
	}

	puts("done");

	free(a);
	free(b);
	free(r);

	return 0;
}

//
// Part 1
//

// Matrix multiplication takes the longest as it is O(n^3)
// The Hadamard function takes log n steps and accesses n^2 elements, so O(n^2 log n)

// Flat profile:
//
// Each sample counts as 0.01 seconds.
//   %   cumulative   self              self     total
//  time   seconds   seconds    calls  Ts/call  Ts/call  name
//  93.51      0.67     0.67                             multiply (matrix.c:20 @ 4008d6)
//   4.19      0.70     0.03                             multiply (matrix.c:19 @ 4008c9)
//   2.79      0.72     0.02                             multiply (matrix.c:19 @ 400974)
//   0.00      0.72     0.00        1     0.00     0.00  hadamard (matrix.c:36 @ 4009af)
//   0.00      0.72     0.00        1     0.00     0.00  multiply (matrix.c:16 @ 400896)
//   0.00      0.72     0.00        1     0.00     0.00  print (matrix.c:58 @ 400afb)

// The line where the arithmetic happens is the slowest.

//
// Part 2
//

// Swapping i, j, k to i, k, j improves performance as it optimises data locality.
// Refer to: http://www.eecs.harvard.edu/~mdw/course/cs61/mediawiki/images/b/bb/Lectures-cacheperf.pdf
