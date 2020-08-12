
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define NTHREADS (4)

struct thread_data {
	pthread_mutex_t mutex_t1;
	pthread_mutex_t mutex_t2;
	int data;
};

void* work1(void* arg) {
	struct thread_data* data = (struct thread_data*) arg;
	for(int i = 0; i < 10000; i++) {
		pthread_mutex_lock(&(data->mutex_t1));

		pthread_mutex_lock(&(data->mutex_t2));
		data->data += 1;
		printf("%d\n", data->data);
		pthread_mutex_unlock(&(data->mutex_t1));
		pthread_mutex_unlock(&(data->mutex_t2));
	}
	return NULL;
}


void* work2(void* arg) {
	
	struct thread_data* data = (struct thread_data*) arg;
	for(int i = 0; i < 10000; i++) {
		pthread_mutex_lock(&(data->mutex_t2));
		//Only a thread that has locked mutex_t2 can be here

		pthread_mutex_lock(&(data->mutex_t1));
		//Only a thread that has locked mutex_t1 can be here

		data->data += 1;
		printf("%d\n", data->data);
		
		pthread_mutex_unlock(&(data->mutex_t1));
		pthread_mutex_unlock(&(data->mutex_t2));
	}
	

	return NULL;
}


int main() {
	
	struct thread_data data = { PTHREAD_MUTEX_INITIALIZER, 
		PTHREAD_MUTEX_INITIALIZER,
		0
	};

	pthread_t threads[2];
	pthread_create(threads, NULL, work1, &data);
	pthread_create(threads+1, NULL, work2, &data);


	for(int i = 0; i < 2; i++) {
		pthread_join(threads[i], NULL);
	}
	
	return 0;
}

