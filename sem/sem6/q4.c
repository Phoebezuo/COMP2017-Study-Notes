#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int str_cmp(const void* a, const void* b) {
	return strcmp(a, b);
}


int main() {

	char strs[5][20] = {
		"Jeff",
		"John",
		"Corona",
		"Tyson",
		"Scomo"
	};

	// qsort(strs, 5, 20, str_cmp);

	/*for(int i = 0; i < 5; i++) {
		puts(strs[i]);
	}*/

	char* s = bsearch("Scomo", strs, 5, 20, str_cmp);

	puts(s);

	return 0;
}
