#include <stdio.h>

int my_strlen(const char* s) {
    int count = 0;
    // while (*s) {
        // count++;
        // s++;
    // }
    if(s != NULL) {
		for(int i = 0; s[i] != '\0'; i++) {
			count++;
		}
	}
    return count;
}

int main(void) {
    printf("%d\n", my_strlen("")); // should output 0
    printf("%d\n", my_strlen("123")); // should output 3
    printf("%d\n", my_strlen("abc\n")); // should output 4
    printf("%d\n", my_strlen("lorem\0ipsum\n")); // should output 5
    printf("%d\n", my_strlen("lorem ipsum\n")); // should output 12
    return 0;
}
