#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) 
{
	printf("hello, I am program 1: %d\n", getpid());

    int i;
    for (i = 0; i < argc; ++i)
        printf("%d: %s\n", i, argv[i]);

    return 0;
}
