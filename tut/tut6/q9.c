#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/sysctl.h>

double uptime() {
    struct timeval boottime;
    size_t len = sizeof(boottime);
    int mib[2] = { CTL_KERN, KERN_BOOTTIME };
    if(sysctl(mib, 2, &boottime, &len, NULL, 0) < 0) {
        return -1.0;
    }
    time_t bsec = boottime.tv_sec, csec = time(NULL);

    return difftime(csec, bsec);
}

void minutes_on(int sig) {
    printf("%f\n", uptime());
}

void random_num(int sig) {
    FILE* in_file = fopen("/dev/urandom", "r");
    if (!in_file) {
        printf("Error reading file 1\n");
        return;
    }

    char num[1];
    size_t result = fread(num, 1, 1, in_file);
    if (result >= 0) {
        printf("%d\n", num[0]);
    } else {
        printf("Error reading file 2\n");
    }
    fclose(in_file);
}

void tell_joke(int sig) {
    printf("How do you know if your code is delicious?\n");
    printf("Try a byte.\n");
}

void hangup_handler(int sig) {
    printf("I'm going into self-isolation\n");
    printf("I can't respond anymore\n");
}

int main(void) {
    signal(SIGINT, minutes_on);
    signal(SIGUSR1, random_num);
    signal(SIGUSR2, tell_joke);
    signal(SIGHUP, hangup_handler);

    while (true) {
        sleep(1);
    }
}
