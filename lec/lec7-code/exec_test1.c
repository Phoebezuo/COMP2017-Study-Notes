#include <stdio.h>
#include <unistd.h>

int main() {

	printf("hello: %d\n", getpid());
	char *chunk = (char*)malloc(10000);

	int result = execl("simple", "echo", "Moe", 0);
	if (-1 == result) {
		perror("could not exec program");
        // unallocated memory does not matter if execl succeeds!    
        // this code will execute when it fails
        free(chunk);
        return 1;
    } 

    // essentially unreachable if C implementation done correctly!
	
    // unallocated memory does not matter if execl succeeds!    
    // this code will execute when it fails
    free(chunk);

	return 0;
}
