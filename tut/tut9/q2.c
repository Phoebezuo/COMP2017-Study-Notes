#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main() {
    int p2c_pipefd[2];
    int c2p_pipefd[2];

    if (pipe(p2c_pipefd) < 0 || pipe(c2p_pipefd)) {
        perror("Unable to create pipes");
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Failed to fork");
    } else if (pid == 0) {
        // child read message from parent 
        close(p2c_pipefd[1]); // parent to child write 
        close(c2p_pipefd[0]); // child to parent read 

        char buf[10];
        read(p2c_pipefd[0], buf, 9);

        printf(".....Message from parent: %s\n", buf);

        // retrive  current tie set on computer
        sleep(1);
        time_t t;
        struct tm* tm_info = localtime(&t); // statically allocted  memory 
        char time_buf[256];
        strftime(time_buf, 256, " %H:%M%p", tm_info);
        printf("Child: The time is %s!\n", time_buf);

        char* request = "DONE";
        write(c2p_pipefd[1], request, strlen(request) + 1);

        close(p2c_pipefd[0]); // parent read 
        close(c2p_pipefd[1]); // child write 
    } else {
        // parent write to child 
        close(p2c_pipefd[0]); // parent to child read 
        close(c2p_pipefd[1]); // child to parent write 

        printf("Parent: Hi! Do you know what time it is?\n");

        char* request = "TIME";
        write(p2c_pipefd[1], request, strlen(request) + 1);

        char buf[10];
        read(c2p_pipefd[0], buf, 9);
        printf(".....Message from child: %s\n", buf);

        sleep(1);
        printf("Parent: Thank you!\n");

        close(p2c_pipefd[1]); // parent to child write 
        close(c2p_pipefd[0]); // child to parent read 
    }
}