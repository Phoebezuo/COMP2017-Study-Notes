#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
	int fd[2] = {-1};
	printf("fd1: %d %d\n", fd[0], fd[1]);
	
	int ret = pipe(fd);
	printf("fd2: %d %d\n", fd[0], fd[1]);
	
	char buffer_in[20];
	puts("1"); 
	ssize_t nread2 = read(0, buffer_in, 20);
	puts("2"); 
	buffer_in[nread2] = '\0';

	int pid = fork();
	if (0 == pid) {

		// child
		char buffer[20];
		strncpy(buffer, "This is a long sentence, much longer than 20 characters", 20);

		printf("Child is waiting for input..\n");
		ssize_t nread = read(fd[0], buffer, 19);
		if (-1 == nread) {
			perror("error");
		} else {
			buffer[nread] = '\0';
			printf("nread: %zd\n", nread);
			printf("%s\n", buffer);
		}

	} else {

		sleep(1);

		// parent
		printf("child pid is %d\n", pid);

		ssize_t nwritten = write(fd[1], buffer_in, strlen(buffer_in) );
		if (-1 == nwritten) {
			perror("error");
		} else {
			printf("%zd bytes written\n", nwritten);
		}
		printf("parent has completed\n");

	}

	close(fd[0]);
	close(fd[1]);
	return 0;
}
