#include <stdio.h>

#include <signal.h>

// for alarm
#include <unistd.h> 

int toolong = 0;

void wakeup(int arg)
{
	toolong = 1;
}

int main()
{
	toolong = 0;
	signal(SIGALRM, wakeup);
	alarm(3);
	printf("You have 3 seconds to enter a number: ");
	int x;
	scanf("%d", &x);
	if (toolong == 1) {
		printf("Sorry, you took to long\n");
		printf("Program terminated\n");
		return 1;
	}
	
	printf("blue skies, happiness and unicorns %d\n", x);
	
	return 0;
}

