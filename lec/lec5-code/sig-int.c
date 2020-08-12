#include <stdio.h>
#include <signal.h>
#include <unistd.h> 

volatile int interrupted = 0;

void impatient(int arg)
{
	interrupted = 1;
}

int main()
{
	void (*variable)(int) = impatient;
	signal(SIGINT, variable);
	printf("We are going to do something for a long time\n");
	
	while (!interrupted)
		usleep(10);
	
	printf("Oh..you didn't like waiting\n");
	printf("Program terminated\n");
	
	return 0;
}

