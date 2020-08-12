#include <stdio.h>

int main()
{
	while ( ! feof(stdin) ) {
	   int num;
	   int nread = fscanf(stdin, "%d", &num);
	   if (nread <= 0) 
		  break;
	   fprintf(stdout, "num: %d\n", num);
	}


	return 0;
}
