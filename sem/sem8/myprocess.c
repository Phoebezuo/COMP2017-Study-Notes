#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int main() {

	//fork() -> check if parent, then fork() again
	// 1 -> Parent
	// 1 -> 2
	// 1 -> 3

	//fork() -> not check
	//
	// pid_t p = fork();
	// p = fork();
	// 
	// 1 -> 2
	// 1 -> 3
	// 2 -> 4
	//

	puts("Before forking!");
	fflush(stdout);
	pid_t pid = fork();
	pid_t current_pid = getpid();
	if(pid < 0) {
		fprintf(stderr, "Unable to fork!");
		return 0;
	} else if (pid == 0) {
		//This is the child
		sleep(7);
		puts("I am the child!");
		printf("%d %d\n", pid, current_pid);
	} else {
		sleep(5);
		puts("I am the parent!");
		printf("%d %d\n", pid, current_pid);
	}
	return 0;
}
