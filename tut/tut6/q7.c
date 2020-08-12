#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

int main(void) {
    signal(SIGINT, SIG_IGN);

    while (true) {
        sleep(1);
    }

    return 0;
}
