#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>



int main() {

	/*
		e.g. a read only file 
		1        0      1     1
		Create   Write  Read  Execute
	*/
l
	int fd = open("MYSTDERR", O_CREAT | O_WRONLY);
	close(STDERR_FILENO);

	dup(fd);

	char str[40] = "Hello from stderr file!";
	write(STDERR_FILENO, str, sizeof(str));

	fprintf(stderr, "This is another line from me!");
	close(fd);
	return 0;
}
