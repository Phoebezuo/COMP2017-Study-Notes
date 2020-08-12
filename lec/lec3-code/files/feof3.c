#include <stdio.h>

int main()
{
	FILE *fp = fopen("twonum.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "could not open file for reading\n");
		return 1;
	}
	while ( ! feof(fp) ) {
	   int num;
	   int nread = fscanf(fp, "%d", &num);
	   if (nread <= 0)
		   break;
	   fprintf(stdout, "num: %d\n", num);
	}
	fclose(fp);
	
	return 0;
}
