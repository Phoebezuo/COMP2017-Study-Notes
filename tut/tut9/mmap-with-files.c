#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/mman.h>

#define SOME_DATA (24)

int main(int argc, char ** argv) { 
    if(argc != 2) { 
        //Need two arguments 
        return 1; 
    }

    char * block = NULL; 
    int fd = open(argv[1], O_RDONLY); 
    struct stat stat_b; 

    // int fstat(int fildes, struct stat *buf);
    fstat(fd, &stat_b); 

    // void* mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
    block = mmap(NULL, stat_b.st_size, PROT_WRITE|PROT_READ, MAP_PRIVATE, fd, 0);

    if(block == MAP_FAILED) { 
        perror("MMAP Failed"); 
        close(fd); 
        return 1; 
    } 

    //Read some bytes 
    for(size_t i = 0; i < SOME_DATA; i++) {
        printf("%c", block[i]); 
    } 
    printf("\njob finish\n"); 

    // int munmap(void *addr, size_t len);
    munmap(block, stat_b.st_size); 
    close(fd);
}