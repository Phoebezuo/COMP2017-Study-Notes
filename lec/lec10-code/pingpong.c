#include <dispatch/dispatch.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "semaphore.h"

sem_t ping_lock;
sem_t pong_lock;

void * T1(void * arg) {
	for (;;) {
		printf("%d\n", sem_wait(&ping_lock));
		printf("ping\n");
		// sleep half a second
		usleep(500000);
		printf("%d\n", sem_post(&pong_lock));
		// sem_post(&pong_lock);
	}
}

void * T2(void * arg) {
	for (;;) {
		sem_wait(&pong_lock);
		printf ("pong\n");
		// sleep one second
		usleep(1000000);
		sem_post(&ping_lock);
	}
}

int main() {
	
	// ping to go first
	sem_init(&ping_lock, 0, 1);
	sem_init(&pong_lock, 0, 0);

	pthread_t th[2];
	pthread_create(th+0, NULL, T1, NULL);
	pthread_create(th+1, NULL, T2, NULL);
	
	// wait for threads to finish
	pthread_join(th[0], NULL);
	pthread_join(th[1], NULL);

	return 0;
}