#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void) {
    int n = 4;
    puts("about to fork");
    pid_t pid = fork();
    if (pid < 0) {
        perror("unable to fork");
        return 1;
    }
    if (pid == 0) {
        puts("child"); 
        n++;
        sleep(1);
    } else {
        puts("parent");
        n *= 2;
        wait(NULL);
    }
    printf("fork returned %d, n is %d\n", pid, n);
    return 0;
}
