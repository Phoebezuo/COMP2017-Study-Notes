/* hello.c */
#include <stdio.h>

// symbol for linker
extern const char * foo();

// symbol for linker
int global_size = 0;

// local variables to the module
static char *msg = "Sometihng special";

// local functions
static void print_message() {
	printf("%s\n", msg);
}

// symbol for linker
int main() {

	// local variables to the function
	int x = 0;
	int y = 1 - x;
	
	const char *string = foo();
	printf("%s\n", string);

	printf("%p: \n", foo);

	// substitute msg -> 0x3017
	printf("%s\n", msg);

	return 0;
}
