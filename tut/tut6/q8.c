#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void sigusr_handler(int signo, siginfo_t* sinfo, void* context) {
    time_t rawtime;
    time(&rawtime);

    struct tm *timeinfo = localtime(&rawtime);
    printf("%s", asctime(timeinfo));
}

void sigint_handler(int sig) {
    printf("\nShutting down\n");
    exit(0);
}

int main() {
    // better approach
    struct sigaction sig;
    memset(&sig, 0, sizeof(struct sigaction));
    sig.sa_sigaction = sigusr_handler;
    sig.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sig, NULL);

    // original method, but cannot use in the future
    signal(SIGINT, sigint_handler);

    while (1) {
        sleep(1);
    }

    return 0;
}
