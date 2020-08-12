#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_TEST (10)

#include "stack.h"

int main(int argc, char** argv) {
	int n = DEFAULT_TEST;
	if(argc > 1) {
		// strtol(const char* restrict str, char** restrict endptr, int base)
		n = strtol(argv[1], NULL, 10);
	}

	stack* s = stack_alloc();

	for(int i = 0; i < n; i++) {
		#if DEBUG
			printf("Pushing %d\n", i);
		#endif
		push(s, i);
	}

	for(int i = 0; i < n; i++) {
		s_result res = pop(s);
		if(!res.failed) {
			#if DEBUG
				printf("Value: %d\n", res.val);
			#endif
		} else {
			fprintf(stderr, "No element returned\n");
		}
	}

	printf("runnning\n");

	stack_free(s);
}
