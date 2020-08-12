f#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUF_SIZE (1024)
#define ARG_SIZE (512)
#define BIN_PATH "/bin/"

int main() {
	char arg0[ARG_SIZE];
	char arg1[ARG_SIZE];
	char buf[BUF_SIZE];
	char* n_check = NULL;
	while(1) {
		printf("> ");
		n_check = fgets(buf, BUF_SIZE, stdin);
		sscanf(buf, "%s %s", arg0, arg1);
		// int sscanf(const char *restrict s, const char *restrict format, ...);

		if(strcmp(arg0, "exit") == 0) { break; }
		
		if(n_check != NULL) {
			pid_t pid = fork();
			if(pid == 0) {
				snprintf(buf, BUF_SIZE, BIN_PATH"%s", arg0);
				// int sprintf(char *restrict str, const char *restrict format, ...);
				execl(buf, arg0, arg1, NULL);
				return 0;
			}
		}
	}
}

