#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
	int fd[2] = {-1};
	int ret = pipe(fd);

	char buffer_in[20];
	ssize_t nread2 = read(0, buffer_in, 20);
	buffer_in[nread2] = '\0';

	ssize_t nwritten = write(fd[1], buffer_in, strlen(buffer_in) );
	if (-1 == nwritten) {
		perror("error");
	} else {
		printf("bytes has written: %zd\n", nwritten);
	}
	
	char buffer[20];
	strncpy(buffer, "This is a long sentence, much longer than 20 characters", 20); 

	// ssize_t nread = read(fd[0], buffer_in, 19);
	ssize_t nread = read(fd[0], buffer, 19);

	if (-1 == nread) {
		perror("error");
	} else {
		buffer[nread] = '\0';
		printf("bytes has read: %zd\n", nread);
		printf("text has read: %s\n", buffer);
	}

	close(fd[0]);
	close(fd[1]);
	return 0;

}
