#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define EXCHANGES 10

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static sem_t alice_box;
static sem_t bob_box;

// uses semaphores so we don't lose signals

void* alice(void* arg) {

	for (size_t i = 0; i < EXCHANGES; ++i) {
		puts("Alice: Waiting for Bob to signal");

		// Wait for mail
		sem_wait(&alice_box);
		pthread_mutex_lock(&mutex);

		puts("Alice: Got Bob's signal");
		printf("Alice: Got mail (%zu) from Bob\n", i);

		// Send mail to Bob
		sem_post(&bob_box);
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

void* bob(void* arg) {

	for (size_t i = 0; i < EXCHANGES; ++i) {
		puts("Bob: Waiting for Alice to signal");

		// Wait for mail
		sem_wait(&bob_box);
		pthread_mutex_lock(&mutex);

		puts("Bob: Got Alice's signal");
		printf("Bob: Got mail (%zu) from Alice\n", i);

		// Send mail to Alice
		sem_post(&alice_box);
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

int main(void) {

	sem_init(&alice_box, 0, 1);
	sem_init(&bob_box, 0, 1);

	pthread_t alice_tid;
	pthread_t bob_tid;

	pthread_create(&alice_tid, NULL, alice, NULL);
	pthread_create(&bob_tid, NULL, bob, NULL);

	pthread_join(alice_tid, NULL);
	pthread_join(bob_tid, NULL);

	sem_destroy(&alice_box);
	sem_destroy(&bob_box);

	return 0;
}
