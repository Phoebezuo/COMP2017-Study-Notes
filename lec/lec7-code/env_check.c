#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	int i = 0;

	printf("string %p\n", "constant string");
	printf("address of argv[1] is %p\n", argv[1]);
	printf("address of i %p\n", &i);

	while (1)
	{
		printf("%s\n", envp[i]);
		i++;
		if (envp[i] == NULL)
			break;
	}

	return 0;
}