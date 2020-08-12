#include <errno.h>

// extern int errno;

#include <stdio.h>
#include <stdlib.h>

void foo() {
	FILE *fp = fopen("doesn't exist", "r");
}

int main() {

	perror("first line of code");

	foo();
	printf("errno: %d\n", errno);
	perror("we tried to read a file");

	errno = 0;

	int x = 5;
	printf("errno: %d\n", errno);

	void *data = malloc(-1);
	printf("errno: %d\n", errno);

	free(data);
	printf("errno: %d\n", errno);

	return 0;
}
