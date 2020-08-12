#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	/*
		0 - stdin
		1 - stdout
		2 - stderr
		... rest newly opened files
		3 - my_text.txt


	*/


	int fd = open("./my_text.txt", O_CREAT | O_WRONLY | O_TRUNC);
	FILE* file = fdopen(fd, "w");
	char str[] = "We are now using the FILE* type now with more fputs!!\n";
	fputs(str, file);

	fclose(file);
	return 0;
}
