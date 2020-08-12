#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#define EXCHANGES 10

bool alice_has_mail = false;
bool bob_has_mail = false;

pthread_mutex_t alice_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t alice_signal = PTHREAD_COND_INITIALIZER;

pthread_mutex_t bob_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t bob_signal = PTHREAD_COND_INITIALIZER;

void* alice(void* arg) {
	for(unsigned i = 0; i < EXCHANGES; ++i) {
		pthread_mutex_lock(&alice_mutex);
		while (!alice_has_mail) {
			puts("Alice: Waiting for Bob to signal");
			pthread_cond_wait(&alice_signal, &alice_mutex);
			puts("Alice: Got Bob's signal");
		}
		pthread_mutex_unlock(&alice_mutex);
		
		alice_has_mail = false;
		bob_has_mail = true;

		pthread_cond_signal(&bob_signal);
		printf("Alice: Got mail (%d) from Bob\n", i);
	}
	return NULL;
}

void* bob(void* arg) {
	for(unsigned i = 0; i < EXCHANGES; ++i) {
		pthread_mutex_lock(&bob_mutex);
		while (!bob_has_mail) {
			puts("Bob: Waiting for Alice to signal");
			pthread_cond_wait(&bob_signal, &bob_mutex);
			puts("Bob: Got Alice's signal");
		}
		pthread_mutex_unlock(&bob_mutex);

		alice_has_mail = true;
		bob_has_mail = false;

		pthread_cond_signal(&alice_signal);
		printf("Bob: Got mail (%d) from Alice\n", i);
	}
	
	return NULL;
}

int main(void) {

	pthread_t alice_tid;
	pthread_t bob_tid;
	
	pthread_create(&alice_tid, NULL, alice, NULL);
	pthread_create(&bob_tid, NULL, bob, NULL);

	// start the chain
	bob_has_mail = true;
	pthread_cond_signal(&bob_signal);

	pthread_join(alice_tid, NULL);
	pthread_join(bob_tid, NULL);
	
	return 0;
}
