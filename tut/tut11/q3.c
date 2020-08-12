#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <pthread.h>
#include <unistd.h>

#define THINKERS 5

static pthread_mutex_t chopsticks[THINKERS]; 

void* dine(void* arg) {
    const unsigned id = *((unsigned * ) arg); 
    while (true) { 
        // the ith philosopher can only reach the ith and (i + 1)th chopstick 
        if (id < ((id+1) % THINKERS)) {
            pthread_mutex_lock(&chopsticks[id]);
            pthread_mutex_lock(&chopsticks[(id + 1) % THINKERS]);
        } else {
            pthread_mutex_lock(&chopsticks[(id + 1) % THINKERS]);
            pthread_mutex_lock(&chopsticks[id]);
        }

        printf("Philosopher %u is eating\n", id);
        usleep(500000);
        pthread_mutex_unlock(&chopsticks[id]);
        pthread_mutex_unlock(&chopsticks[(id + 1) % THINKERS]);
    }
    return NULL;
}

int main(void) {
    unsigned args[THINKERS]; pthread_t thinkers[THINKERS];

    // create the chopsticks 
    for (size_t i = 0; i < THINKERS; i++) { 
        if (pthread_mutex_init(chopsticks + i, NULL) != 0) { 
            perror("unable to initialize mutex"); 
            return 1; 
        } 
    }

    // launch threads 
    for (size_t i = 0; i < THINKERS; i++) {
        args[i] = i;
        if (pthread_create(thinkers + i, NULL, dine, args + i) != 0) { 
            perror("unable to create thread"); return 1; 
        }
    }
    
    // wait for threads to finish 
    for (size_t i = 0; i < THINKERS; i++) { 
        if (pthread_join(thinkers[i], NULL) != 0) { 
            perror("unable to join thread"); 
            return 1; 
        } 
    }
    
    // remove the chopsticks 
    for (size_t i = 0; i < THINKERS; i++) { 
        if (pthread_mutex_destroy(chopsticks + i) != 0) { 
            perror("unable to destroy mutex"); 
            return 1; 
        } 
    }

    return 0;
}