#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int *numbers = NULL;
int numbers_size = 0;

int main() {

	numbers = (int*)malloc(10 * sizeof(int));
	numbers_size = 10;
	numbers[0] = 999;

	printf("hello: %d\n", getpid());

	int result = fork();

	char *owner = "parent";
	if (result == 0){
		printf("I am the child: %d\n", getpid());
		owner = "child";
		printf("%s: numbers_size: %d\n", owner, numbers_size);
		printf("%s: numbers[0]: %d\n", owner, numbers[0]);
		free(numbers);
		return 0; // terminate program
	} else {
		usleep(10);
		printf("I am the parent: %d\n", getpid());
		printf("%s: numbers_size: %d\n", owner, numbers_size);
		printf("%s: numbers[0]: %d\n", owner, numbers[0]);
		numbers[0] = 876;
		printf("%s: numbers[0]: %d\n", owner, numbers[0]);
		free(numbers);
	}

	printf("%s world: %d\n", owner, getpid());

	return 0; // terminate program
}
