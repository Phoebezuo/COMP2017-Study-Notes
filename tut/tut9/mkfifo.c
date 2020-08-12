#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SZ (256)
#define CHANNEL_NAME ("comm");

int main() { 
    if((mkfifo(CHANNEL_NAME, S_IRWXU | S_IRWXG)) >= 0) { 
        int fd = open(CHANNEL_NAME, O_RDONLY); // read only 
        if(fd > 0) { 
            FILE* read_channel = fdopen(fd, "r"); 
            char buf[BUF_SZ]; 
            while(fgets(buf, BUF_SZ, read_channel) != NULL) { 
                puts(buf); 
            } 
            fclose(read_channel); 
        }

    } else { 
        fprintf(stderr, "Unable to open pipe");
    }
    return 0;
}