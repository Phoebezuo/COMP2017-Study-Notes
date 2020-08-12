#include <stdio.h>

int foo(int n, int m) {

	int x = 2;
	int y = 5;

	printf("addr of n is: %p\n", &n);
	printf("addr of m is: %p\n", &m);
	printf("addr of x is: %p\n", &x);
	printf("addr of y is: %p\n", &y);

	return 3;
}

int main() {

	//  line 18

	int ret = foo(4, 2);
	// line 20
	return 0;
}
