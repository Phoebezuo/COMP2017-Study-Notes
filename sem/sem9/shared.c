#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#define PG_SIZE (4096)

int main() {
	int fd = shm_open("/myshare", O_RDWR | O_CREAT, 0777);
	ftruncate(fd, 4096);
	char buf[64] = "Hello from child!";
	char* shared = mmap(NULL, PG_SIZE, PROT_READ | PROT_WRITE,
			MAP_SHARED, fd, 0);
	pid_t pid = fork();

	if(pid == 0) {
		strcpy(shared, buf);
		munmap(shared, PG_SIZE);
		
		shared = mmap(NULL, PG_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
				fd, 0);
		sleep(4);
		fputs(shared, stdout);
		munmap(shared, PG_SIZE);
		
	} else if(pid > 0) {
		sleep(2);
		fputs(shared, stdout);
		strcat(shared+strlen(shared), "Another line!\n");
		munmap(shared, PG_SIZE);
		shm_unlink("/myshare");
	}

	return 0;
}
