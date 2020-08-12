#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>

#define MAIN_THREAD_TIMEOUT (60) 
#define N_JOBS (200)

struct work_data {
    uint32_t time;
    uint32_t work_id;
};

// for queue
struct thread_job {
    void* fn;
    void* data;
};

struct thread_queue_node {
    struct thread_job* job;
    struct thread_queue_node* next;
};

struct thread_queue {
    struct thread_queue_node* head;
    struct thread_queue_node* tail;
    int size;
};

// for thread pool 
struct thread_data {
    struct thread_queue* queue;
    pthread_mutex_t* lock;
    size_t id; 
    int* finished;
};

struct thread_pool {
    size_t n_threads;
    size_t thread_cursor;
    pthread_mutex_t* locks;
    pthread_t* handlers;
    struct thread_data* thread_data;
    int finished; 
};

struct thread_queue* thread_queue_new() {
    struct thread_queue* q = malloc(sizeof(struct thread_queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;

    return q; 
}

void thread_queue_destroy(struct thread_queue* q) {
    if (q) {
        struct thread_queue_node* node = q->head;
        struct thread_queue_node* temp = NULL;
        while (node) {
            temp = node->next;
            free(node);
            node = temp;
        }
        free(q);
    }
}

void thread_queue_enqueue(struct thread_queue* q, struct thread_job* j) {
    if (q) {
        struct thread_queue_node* n = malloc(sizeof(struct thread_queue_node));
        n->job = j;
        n->next = NULL; 

        if (q->head == NULL) {
            q->head = n;
            q->tail = n;
        } else{
            q->tail->next = n;
            q->tail = q->tail->next;
        }

        q->size++;
    }
}

struct thread_job* thread_queue_dequeue(struct thread_queue* q) {
    if (q) {
        if (q->head) {
            struct thread_job* j = q->head->job;
            struct thread_queue_node* next = q->head->next;
            free(q->head);
            q->head = next;
            
            if (q->head == NULL) {
                q->tail = NULL;
            }
            q->size--;
            return j;
        }
    }
    return NULL; 
}

size_t thread_queue_empty(struct thread_queue* q) {
    if (q){
        return q->size == 0;
    }
    return 1;
}

struct thread_job* thread_job_new(void(*fn)(void*), void* data) {
    struct thread_job* job = malloc(sizeof(struct thread_job));
    job->fn = fn;
    job->data = data;
    return job;
}

void thread_job_destroy(struct thread_job* j) {
    free(j);
} 

void* thread_pool_work(void* arg) {
    struct thread_data* data = (struct thread_data*) arg;
    void* targ = NULL;
    void(*fn)(void*) = NULL; 

    while (!(*(data->finished))) {
        pthread_mutex_lock(data->lock);
        while (!thread_queue_empty(data->queue)) {
            printf("Thread %lu: ", data->id);
            struct thread_job* w = thread_queue_dequeue(data->queue);
            fn = w->fn;
            targ = w->data;
            fn(targ);
            free(w);
        }
    }

    thread_queue_destroy(data->queue);
    pthread_mutex_unlock(data->lock);
    pthread_mutex_destroy(data->lock);
    return NULL;
}

struct thread_pool* thread_pool_new(size_t n) {
    struct thread_pool* pool = malloc(sizeof(struct thread_pool));
    pool->n_threads = n;
    pool->thread_cursor = 0;
    pool->locks = malloc(sizeof(pthread_mutex_t) * n);
    pool->handlers = malloc(sizeof(pthread_t) * n);
    pool->thread_data = malloc(sizeof(struct thread_data) * n);
    pool->finished = false;

    for (size_t i = 0; i < n; i++) {
        pthread_mutex_init(pool->locks + i, NULL);
        pthread_mutex_lock(pool->locks + i);
        pool->thread_data[i].queue = thread_queue_new();
        pool->thread_data[i].id = i;
        pool->thread_data[i].finished = &pool->finished;
        pool->thread_data[i].lock = pool->locks + i;
        pthread_create(pool->handlers + i, NULL, thread_pool_work, pool->thread_data + i);
    }
    
    return pool;
}

void thread_pool_execute(struct thread_pool* pool, struct thread_job* msg) {
    if (pool && msg) {
        thread_queue_enqueue(pool->thread_data[pool->thread_cursor].queue, msg);
        pthread_mutex_unlock(pool->locks + pool->thread_cursor);
        pool->thread_cursor = (pool->thread_cursor + 1) % pool->n_threads;
    }
}

void thread_pool_destroy(struct thread_pool* pool) {
    if (pool) {
        puts("Finishing");
        pool->finished = true; 
        
        for (size_t i = 0; i < pool->n_threads; i++) {
            pthread_mutex_unlock(pool->locks + i);
            pthread_mutex_destroy(pool->locks + i);
            pthread_join(pool->handlers[i], NULL);
        }

        free(pool->locks);
        free(pool->handlers);
        free(pool->thread_data);
        free(pool);
    }
}

void mysleep(void* arg) { 
    struct work_data* data = (struct work_data*) arg; 
    printf("is working on job %u\n", data->work_id); 
    fflush(stdout); 
    sleep(data->time); 
    free(data); 
}

int main() {
    struct thread_pool* pool = thread_pool_new(8);
    for(size_t i = 0; i < N_JOBS; i++) { 
        struct work_data* d = malloc(sizeof(struct work_data));
        d->time = 1;
        d->work_id = i;
        struct thread_job* job = thread_job_new(mysleep, d); 
        thread_pool_execute(pool, job);
    } 
    sleep(MAIN_THREAD_TIMEOUT); 
    thread_pool_destroy(pool); 
    puts("Finishing up now!"); 
    return 0;
}