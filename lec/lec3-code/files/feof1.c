#include <stdio.h>

int main()
{
	while ( ! feof(stdin) ) {
	   int num;
	   fscanf(stdin, "%d", &num);
	   fprintf(stdout, "num: %d\n", num);
	}

	return 0;
}
