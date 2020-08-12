#include <unistd.h>
#include <fcntl.h>

int main() {
	int fd = open("./my_text.txt", O_CREAT | O_WRONLY | O_TRUNC);
	char str[] = "This is new text!";
	write(fd, str, sizeof(str));


	return 0;
}
