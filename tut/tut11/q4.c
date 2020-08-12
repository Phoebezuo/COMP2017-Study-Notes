#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 5

sem_t table;

void* dine(void* arg) {

	const unsigned id = *(unsigned *) arg;

	for (size_t i = 0; i < 100; i++) {
		sem_wait(&table);
		printf("Philosopher %u is eating\n", id);
		sem_post(&table);
	}

	return NULL;
}

int main(void) {

	unsigned args[NTHREADS];
	pthread_t thinkers[NTHREADS];

	sem_init(&table, 0, NTHREADS / 2);

	for (size_t i = 0; i < NTHREADS; ++i) {
		args[i] = i;
		pthread_create(thinkers + i, NULL, dine, args + i);
	}

	for (size_t i = 0; i < NTHREADS; ++i) {
		pthread_join(thinkers[i], NULL);
	}

	sem_destroy(&table);

	return 0;
}
