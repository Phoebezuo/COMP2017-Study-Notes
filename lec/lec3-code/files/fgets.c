#include <stdio.h>
#include <string.h>

#define BUFLEN (12)

int main(int argc, char **argv) 
{
	FILE* fp;
	const char *fname = "sample.txt";

	fp = fopen(fname, "r");
	if (fp == NULL) {
		fprintf(stderr, "could not open file %s\n", fname);
		return 1;
	}

	int len;
	char buf[BUFLEN];
	while (fgets(buf, BUFLEN, fp) != NULL) {
		len = strlen(buf);
		printf("line is :%s and length is: %d\n", buf, len);
	}

	fclose(fp);

	return 0;
}
