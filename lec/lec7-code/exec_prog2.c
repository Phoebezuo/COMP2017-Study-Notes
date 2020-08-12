#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) 
{
	printf("hello, I am program 2: %d\n", getpid());

    int i;
    for (i = 0; i < argc; ++i)
        printf("%d: %s\n", i, argv[i]);

    if (-1 == execl("exec_prog1", "Silly executable name", "1st arg", "2nd arg", 0))
        perror("could not execute exec_prog1");
    
	printf("program 2 continues sadly: %d\n", getpid());
    
    return 0;
}
