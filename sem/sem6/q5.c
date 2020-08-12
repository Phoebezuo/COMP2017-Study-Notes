#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int finished = 0;

void int_handler(int signo) {
	puts("INT Handler");
	finished = 1;
	printf("%d\n", signo);
}




int main() {
	signal(SIGINT, int_handler);
	signal(SIGHUP, int_handler);
	signal(SIGUSR1, int_handler);
	while(!finished) {
	}

	puts("We are finishing up!");
}
