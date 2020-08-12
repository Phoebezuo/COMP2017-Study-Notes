#include <stdio.h>
#include <unistd.h>


int main() {

	printf("hello: %d\n", getpid());

	int result = fork();

	char *owner = "parent";
	if (result == 0){
		printf("I am the child: %d\n", getpid());
		owner = "child";
	} else {
		usleep(10);
		printf("I am the parent: %d\n", getpid());
	}

	printf("%s world\n", owner);

	return 0;

}
