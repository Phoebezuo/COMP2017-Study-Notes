#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pipe(pipefd);

    pid_t pid = fork();

    if (pid == 0) {
        // child read message from parent 
        char buffer[50];
        close(pipefd[1]); // write end of pipe 
        int num_read = read(pipefd[0], buffer, 50);
        if (num_read < 0) {
            perror("error happened");
        }
        close(pipefd[0]); // read end of pipe 
        printf("Child: I will use the password %s\n", buffer); 
    } else if (pid > 0) {
        //  parent write to child  
        close (pipefd[0]); // read end of pipe 
        char* password = "\"grilledcheese\"";
        printf("Parent: The password is %s\n", password); 
        write(pipefd[1], password, strlen(password));
        close(pipefd[1]);
        wait(0);
    } else {
        perror("some error");
        exit(1); 
    }
}