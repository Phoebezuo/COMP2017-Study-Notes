#include <stdio.h>
#include <unistd.h>

int main() {

	printf("hello: %d\n", getpid());

	fork();

	printf("world: %d\n", getpid());

	return 0;

}
