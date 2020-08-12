#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NWHITE (1000)
#define NRED   (NWHITE * 2)

sem_t red_pairs;
sem_t white_mutex;
pthread_barrier_t stage;

void* red(void *arg) {

	// Using a semaphore that allows only two red threads to enter
	// Using a barrier to wait for the white thread to enter

	sem_wait(&red_pairs);
	pthread_barrier_wait(&stage);
	sem_post(&red_pairs);

	return NULL;
}

void* white(void *arg) {

	// Using a mutex that allows only one white thread to enter
	// Using a barrier to wait for the other two red threads

	sem_wait(&white_mutex);
	pthread_barrier_wait(&stage);
	sem_post(&white_mutex);

	return NULL;
}

int main(void) {

	sem_init(&red_pairs, 0, 2);
	sem_init(&white_mutex, 0, 1);
	pthread_barrier_init(&stage, NULL, 3);

	pthread_t thread_ids[NRED + NWHITE];

	for (size_t i = 0; i < NWHITE; ++i) {
		pthread_create(thread_ids + i * 3 + 0, NULL, red, NULL);
		pthread_create(thread_ids + i * 3 + 1, NULL, red, NULL);
		pthread_create(thread_ids + i * 3 + 2, NULL, white, NULL);
	}

	for (size_t i = 0; i < NRED + NWHITE; ++i) {
		pthread_join(thread_ids[i], NULL);
	}

	pthread_barrier_destroy(&stage);

	return 0;
}
