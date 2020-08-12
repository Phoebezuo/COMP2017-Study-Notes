#include <stdio.h>

int i = 0;

void* state1();
void* f();

void* state1() {	
	i++;
	puts("Hello from state1");
	if((i % 2) == 0) {
		return state1;	
	} else {
		return f;
	}
}



void* f() {
	i++;
	puts("Hello from f");
	if((i % 2) == 0) {
		return state1;	
	} else {
		return f;
	}
}


int main() {
	void* (*fn)() = f;

	fn = fn();
	fn = fn();
	fn = fn();
	return 0;
}
