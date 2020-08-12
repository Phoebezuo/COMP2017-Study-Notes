#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) 
{
	printf("hello, I am program 3: %d\n", getpid());

    int i;
    for (i = 0; i < argc; ++i)
        printf("%d: %s\n", i, argv[i]);

    if (-1 == execl("exec_prog2", "exec_prog2", "index[1]", "index[2]", "index[3]", 0 ))
        perror("could not execute exec_prog2");
    
	printf("program 3 continues sadly: %d\n", getpid());
    
    return 0;
}
