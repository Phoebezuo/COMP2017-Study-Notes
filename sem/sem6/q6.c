#include <stdio.h>
#include <stdlib.h>


int f(int x, int y) {
	return x + y;
}


void g(int y) {
	
}


int main() {
	int (*fn)(int, int) = f;

	int res = fn(1, 5);
	printf("%d\n", res);
	fn = g;

	res = fn(5, 6);

	printf("%d\n", res);
	return 0;
}
