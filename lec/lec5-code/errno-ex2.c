#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void foo() {
	FILE *fp = fopen("doesn't exist", "r");
}

int main() {
	foo();
	printf("errno: %d\n", errno);
	perror("");

	int x = 5;
	printf("errno: %d\n", errno);
	perror("");

	void *data = (void*)malloc(1);
	printf("errno: %d\n", errno);
	perror("");

	free(data);
	printf("errno: %d\n", errno);
	perror("");

	FILE *fp2 = fopen("skinner.txt", "r");
	printf("errno: %d\n", errno);
	perror("");

	return 0;
}


