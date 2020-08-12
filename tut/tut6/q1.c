#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    write(STDERR_FILENO, "hello world\n", strlen("hello world\n"));
}
