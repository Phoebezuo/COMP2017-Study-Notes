#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/mman.h> 
#include <fcntl.h> 
#include <unistd.h> 
#define DATA_SIZE (6)

int * give_data() { 
    int* data = malloc(sizeof(int) * DATA_SIZE); 
    for(int i = 0; i < DATA_SIZE; i++) { 
        data[i] = i; 
    } 
    return data; 
}

void read_share(int* d) { 
    for(int i = 0; i < DATA_SIZE; i++) { 
        printf("%d\n", d[i]); 
    } 
}

int main() { 
    int* d = give_data(); 
    int* shared = mmap(NULL, DATA_SIZE * sizeof(int), PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0); 
    memcpy(shared, d, DATA_SIZE * sizeof(int)); 
    free(d); 
    pid_t p = fork();

    if(p == 0) {
        printf("Child\n"); 
        read_share(shared); 
        for(int i = 0; i < DATA_SIZE; i++) { 
            shared[i] = i + 10; 
        } 
        munmap(shared, DATA_SIZE * sizeof(int)); 
    } else if(p > 0) { 
        sleep(2); 
        printf("Parent\n"); 
        read_share(shared); 
        munmap(shared, DATA_SIZE * sizeof(int)); 
    } 
    return 0;
}