#include <stdio.h>

int doit(int c) {
	float f = 3.0f;

	static int d = 0;

	d++;
	printf("addr of c is %p\n", &c);
	printf("addr of f is %p\n", &f);
	printf("addr of d is %p\n", &d);
	printf("addr of \"hello\" is %p\n", "hello");

	return d;
}

int main() {

	int res = doit(4);
	res = doit(4);
	printf("res is : %d\n", res);

	return 0;
}	

