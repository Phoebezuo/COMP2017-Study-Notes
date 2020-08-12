#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define LENGTH 100000000
#define NTHREADS 4
#define NREPEATS 10
#define CHUNK (LENGTH / NTHREADS)

typedef struct {
	size_t id;
	long* array;
	long result;
} worker_args;

void* worker(void* args) {

	worker_args* wargs = (worker_args*) args;

	const size_t start = wargs->id * CHUNK;
	const size_t end = wargs->id == NTHREADS - 1 ? LENGTH : (wargs->id + 1) * CHUNK;

	// Use local stack variable to prevent false sharing
	long sum = 0;

	// Sum values from start to end
	for (size_t i = start; i < end; i++) {
		sum += wargs->array[i];
	}

	wargs->result = sum;
	return NULL;
}

int main(void) {

	long* numbers = malloc(sizeof(long) * LENGTH);
	for (size_t i = 0; i < LENGTH; i++) {
		numbers[i] = i + 1;
	}

	worker_args* args = malloc(sizeof(worker_args) * NTHREADS);
	for (size_t n = 1; n <= NREPEATS; n++) {
		for (size_t i = 0; i < NTHREADS; i++) {
			args[i] = (worker_args) {
				.id     = i,
				.array  = numbers,
				.result = 0,
			};
		}

		pthread_t thread_ids[NTHREADS];

		// Launch threads
		for (size_t i = 0; i < NTHREADS; i++) {
			pthread_create(thread_ids + i, NULL, worker, args + i);
		}

		// Wait for threads to finish
		for (size_t i = 0; i < NTHREADS; i++) {
			pthread_join(thread_ids[i], NULL);
		}

		long sum = 0;

		// Calculate total sum
		for (size_t i = 0; i < NTHREADS; i++) {
			sum += args[i].result;
		}

		printf("Run %2zu: total sum is %ld\n", n, sum);
	}

	free(args);
	free(numbers);
}
