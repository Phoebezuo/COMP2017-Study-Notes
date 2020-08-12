#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>


int main() {

	int fd = open("mystdout.txt", O_CREAT | O_RDWR | O_TRUNC);

	close(STDOUT_FILENO);
	dup(fd);
	char* args[] = {
		"echo",
		"Hello World!",
		NULL
	};

	pid_t pid = fork();


	if(pid == 0) {
		if(execv("/usr/bin/echo", args) == -1) {
			fprintf(stderr, "exec failed!");
		}
	} else if(pid > 0) {
		wait(NULL);
		char buf[100];
		FILE* f = fdopen(fd, "rw");
		
		fseek(fd, 0, SEEK_SET);
		ssize_t bytes = read(fd, buf, 100);
		fprintf(stderr, "%ld\n", bytes);

		fprintf(stderr, "%s\n", buf);

		fclose(f);
	}

	return 0;
}
