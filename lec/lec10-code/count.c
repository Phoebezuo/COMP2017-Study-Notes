#include <stdio.h>
#include <pthread.h>

#define MAX 2 
#define MAX_ITER 100000000

long counter = 0;

void * thread_function(void * arg) {
	long l;
	for (l = 0; l < MAX_ITER; l++)
		counter++; //critical section
	return NULL;
}

int main(void) {
	pthread_t mythread[MAX]; int t = 0;

	for (t = 0; t < MAX; t++)
		pthread_create( &mythread[t], NULL, thread_function, NULL);

	for (t = 0; t < MAX; t++)
		pthread_join ( mythread[t], NULL);

	printf("Expected counter value: %d, observed counter value: %ld\n", MAX_ITER * MAX, counter);
	printf("You experienced %ld race conditions, or %ld%% of all accesses to the shared variable.\n", MAX_ITER * MAX - counter, 100 - 100 * counter / (MAX_ITER * MAX));

	return 0;
}
