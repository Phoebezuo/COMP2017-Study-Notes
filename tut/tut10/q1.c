#include <stdio.h> 
#include <pthread.h>

#define NTHREADS 4

void* worker(void * arg) { 
    const int argument = *((int * ) arg); 
    printf("Hello from thread %d\n", argument); 
    return NULL;
}

int main(void) {
    int args[NTHREADS] = { 1, 2, 3, 4 };
    pthread_t thread_ids[NTHREADS];

    // Create threads with given worker function and argument 
    for (size_t i = 0; i < NTHREADS; i++) { 
        if (pthread_create(thread_ids + i, NULL, worker, args + i) != 0) { 
            perror("unable to create thread"); 
            return 1; 
        } 
    }
    
    // Wait for all threads to finish 
    for (size_t i = 0; i < NTHREADS; i++) {
        if (pthread_join(thread_ids[i], NULL) != 0) { 
            perror("unable to join thread"); 
            return 1;
        }
    }
}