#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main() {
	int fd = open("tmpfile", O_RDONLY | O_NONBLOCK);
	if (-1 == fd) {
		perror("failed to open file");
		return 1;
	}

	printf("fd: %d\n", fd);
	fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);

	char buffer[100];
	while (1) {
		ssize_t nread = read(fd, buffer, 10);
		if (-1 == nread) {
			if (errno == EAGAIN) {
				printf("stop the blocking call to read\n");
			} else {
				perror("something wrong");
			}
			sleep(1);
			continue;
		}
		else if (0 == nread) {
			if (errno == EAGAIN) {
				printf("stop the blocking call to read\n");
				sleep(1);
				continue;
			} else {
				// end of file?
				break;
			}
		} else {
			buffer[nread] = '\0';
			printf("new data: %s\n", buffer);
		}
	}
	printf("Program ended\n");
	close(fd);

	return 0;
}

