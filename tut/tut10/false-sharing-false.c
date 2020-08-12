#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define MAX_SIZE 100000000

typedef struct {
    int first;
    int last;
    int id;
} MY_ARGS;

int* arr;
int results[2];

void* myfunc(void* args) {
    int i;
    MY_ARGS* my_args = (MY_ARGS*) args;
    int first = my_args->first;
    int last = my_args->last;
    int id = my_args->id;;

    for (i = first; i < last; i++) {
        results[id] = results[id] + arr[i];
    }

    return NULL; 
}

int main() {
    int i = 0;
    arr = malloc(sizeof(int) * MAX_SIZE);
    for (int i = 0; i < MAX_SIZE; i++) {
        arr[i] = rand() % 5;
    }
    results[0] = 0;
    results[1] = 0;

    pthread_t th1;
    pthread_t th2; 
    
    int mid = MAX_SIZE / 2;
    MY_ARGS args1 = {0, mid, 0};
    MY_ARGS args2 = {mid, MAX_SIZE, 1};

    pthread_create(&th1, NULL, myfunc, &args1);
    pthread_create(&th2, NULL, myfunc, &args2);

    pthread_join(th1, NULL); 
    pthread_join(th2, NULL);

    printf("s1 = %d\n", results[0]);
    printf("s2 = %d\n", results[1]);
    printf("s1 + s2 = %d\n", results[0] + results[1]);
    return 0; 
}
