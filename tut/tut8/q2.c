#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t amazing = 0;
volatile sig_atomic_t outside = 0;

void parent_int(int signo) {}

void child_int(int signo) { amazing = 1; }

void child_hup(int signo) { outside = 1; }

int main() {
	pid_t parent = getpid();
	pid_t pid = fork();
	
	if(pid > 0) { //Parent
		pause();
		kill(pid, SIGINT);
		sleep(1); //Just to delay the next signal
		kill(pid, SIGHUP);
	} else if(pid == 0) {
		kill(parent, SIGINT);
		while(1) {
			pause();
			if(amazing) {
				amazing = 0; //reset
				printf("I'm Amazing!\n");
			} else if(outside) {
				printf("I'm going to go play outside!\n");
				break;
			}
		}
	} else {
		printf("It failed!\n");
	}
	return 0;
}
