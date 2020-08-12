/* The purpose of this module is to show 5 different methods
 * to define and use a mutex.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_ITER 10000000
#define MAX 5

long counter[5] = {0,0,0,0,0};

// mutex allocated in static
// mutex initialised with MACRO
pthread_mutex_t static_mutex = PTHREAD_MUTEX_INITIALIZER;

// mutex allocated in static
// mutex initialised at runtime
pthread_mutex_t static_mutex_no_macro;

void* static_based_mutex(void * arg) {
	long l;
	for (l = 0; l < MAX_ITER; l++) {
		pthread_mutex_lock(&static_mutex);
		counter[0]++; //critical section
		pthread_mutex_unlock(&static_mutex);
	}
}

void* stack_based_mutex(void * arg) {
	long l;
	// mutex allocated on stack
	// mutex initialised with MACRO
	pthread_mutex_t stack_mutex = PTHREAD_MUTEX_INITIALIZER;
	for (l = 0; l < MAX_ITER; l++) {
		pthread_mutex_lock(&stack_mutex);
		counter[1]++; //critical section
		pthread_mutex_unlock(&stack_mutex);
	}
}


void* static_based_mutex_no_macro(void* arg) {
	long l;
		
	// mutex initialised with function
	pthread_mutex_init(&static_mutex_no_macro, NULL);
	
	for (l = 0; l < MAX_ITER; l++) {
		pthread_mutex_lock(&static_mutex_no_macro);
		counter[2]++; //critical section
		pthread_mutex_unlock(&static_mutex_no_macro);
	}
}

void* stack_based_mutex_no_macro(void* arg) {
	long l;
	
	// mutex allocated on stack
	pthread_mutex_t stack_mutex;
	
	// mutex initialised with function
	pthread_mutex_init(&stack_mutex, NULL);
	
	for (l = 0; l < MAX_ITER; l++) {
		pthread_mutex_lock(&stack_mutex);
		counter[3]++; //critical section
		pthread_mutex_unlock(&stack_mutex);
	}
}

void* heap_based_mutex(void* arg) {
	long l;
	
	// mutex allocated on heap
	pthread_mutex_t* heap_mutex = malloc(sizeof(pthread_mutex_t));

	// mutex initialised with pthread_mutex_init
	pthread_mutex_init(heap_mutex, NULL);

	for (l = 0; l < MAX_ITER; l++) {
		pthread_mutex_lock(heap_mutex);
		counter[4]++; //critical section
		pthread_mutex_unlock(heap_mutex);
	}
	
	pthread_mutex_destroy(heap_mutex);
	
	// never forget!
	free(heap_mutex);
}



int main(void) {
	pthread_t mythread[MAX]; // specifically 5
	int t = 0;

	pthread_create( &mythread[0], NULL, static_based_mutex, NULL);
	pthread_create( &mythread[1], NULL, stack_based_mutex, NULL);
	pthread_create( &mythread[2], NULL, heap_based_mutex, NULL);
	pthread_create( &mythread[3], NULL, static_based_mutex_no_macro, NULL);
	pthread_create( &mythread[4], NULL, stack_based_mutex_no_macro, NULL);

	for (t = 0; t < MAX; t++)
		pthread_join ( mythread[t], NULL);

	return 0;
}