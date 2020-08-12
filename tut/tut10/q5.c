#include <stdio.h>
#include <pthread.h>

#define THREADS 4
#define LOOPS 10000000

static unsigned counter = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void* worker(void* arg) {
    for (unsigned i = 0; i < LOOPS; i++) {
        // attemp to lock the mutex
        // thread will wait when mutex is already locked 
        pthread_mutex_lock(&mutex);
        // only one thread will be able execute this code
        counter++;
        // unlock the mutex after the critical section
        // pthread_mutex_unlock(&mutex);
    }
    return NULL; 
}

int main(void) {
    pthread_t thread_ids[THREADS];

    for (size_t i = 0; i < THREADS; i++) {
        pthread_create(&thread_ids[i], NULL, worker, NULL);
    }

    for (size_t i = 0; i < THREADS; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    printf("%d\n", counter);
}