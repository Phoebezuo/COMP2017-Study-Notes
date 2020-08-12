#include <stdio.h>
#include <unistd.h>

int main() 
{
	printf("hello: %d\n", getpid());

	int result = execl("/usr/sbin/echo", "echo", "Moe", 0);
	if (-1 == result)
		perror("could not exec program");	
	else {
		printf("This should never happen\n");
	}
	
    // if execl succeeds, we never reach here
	printf("world: %d\n", getpid());

	return 0;
}
