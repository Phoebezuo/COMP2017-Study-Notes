#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
	
	int fd[2];
	pipe(fd);
	pid_t pid = fork();
	
	if(pid == 0) {
        // child 
		close(1);
		close(fd[0]);
		dup(fd[1]); //Gets set to stdout

        // int execlp(const char *file, const char *arg0, ... /*, (char *)0 */);
		execlp("/bin/ls", "ls", "-l", "./", NULL);  // file descriptors are maintained
	} else if(pid > 0) {
        // parent
		FILE* f = fdopen(fd[0], "r");
		char buf[1024];
		int i = 1;
		while((fgets(buf, 1024, f)) != NULL) {
			printf("Line %d: %s", i, buf);
			i += 1;
		}
	}
	
	return 0;
}
