#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

int main() {

	int channel[2];
	pipe(channel); //channel[0] = read, channel[1] = write
	
	pid_t pid = getpid();

	for(int i = 0; i < 8; i++) {
		
		pid = fork();
		if(pid == 0) {
			break;
		}
	}

	if(pid == 0) {
		char buf[64];
		snprintf(buf, 64, "Hello From %d\n", getpid());
		write(channel[1], buf, 64);
		close(channel[1]);
		close(channel[0]);
	} else if(pid > 0) {
		close(channel[1]);
		char buf[64];
		while(1) {
			if(read(channel[0], buf, 64) == -1) {
				break;
			}
			if(errno > 0) {
				break;
			}
			printf("%s", buf);
			wait(NULL);
		}

	}

}
