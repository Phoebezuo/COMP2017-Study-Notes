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

    FILE* fp = fopen(argv[1], "r"); 
    struct stat stat_b; 

    if(stat(argv[1], &stat_b) == -1) { 
        perror("connot get file size\n"); 
        fclose(fp); 
        return 1; 
    } 

    //Read some bytes 
    for(size_t i = 0; i < SOME_DATA; i++) {
        fseek(fp, i, SEEK_SET); 
        printf("%c", fgetc(fp)); 
    } 
    printf("\njob finish\n"); 

    fclose(fp);
}