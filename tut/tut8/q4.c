#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUF_SIZE (1024)
#define ARG_SIZE (512)
#define BIN_PATH "/bin/"

#define PID_LIST_SIZE (1024)

void shift_down(pid_t* pids, size_t sz, size_t idx) {
	for(size_t i = idx; i < sz-1; i++) {
		pids[i] = pids[i+1];
	}
}

int main() {
	char arg0[ARG_SIZE];
	char arg1[ARG_SIZE];
	char buf[BUF_SIZE];
	char* n_check = NULL;
	pid_t pids[PID_LIST_SIZE];
	size_t n_procs = 0;
	
	while (1) {
		printf("> ");
		n_check = fgets(buf, BUF_SIZE, stdin);
		sscanf(buf, "%s %s", arg0, arg1);
		
		for (size_t i = 0; i < PID_LIST_SIZE; i++) {
			int status = 0;
			if (waitpid(pids[i], &status, WNOHANG) == -1) {
				shift_down(pids, PID_LIST_SIZE, i);
			}
			
			if (WIFEXITED(status)) {
				shift_down(pids, PID_LIST_SIZE, i);
			}
		}
		
		if(strcmp(arg0, "exit") == 0) { break; }
		
		if (n_check != NULL) {
			pid_t pid = fork();
			if (pid == 0) {
				snprintf(buf, BUF_SIZE, BIN_PATH"%s", arg0);
				execl(buf, arg0, arg1, NULL);
				return 0;
			}
		}
	}
}

