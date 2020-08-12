#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	char *chars;
	chars = (char*)malloc(10);

	memset(chars, 0x01, 10);
	if ( chars == NULL) {
		/// ...
		return 1;
	}

	int i;
	for (i = 0; i < 4; ++i)
		chars[i] = 'a' + i;
	chars[i] = '\0';
	chars[4] = '\0';

	for (i = 0; i < 10; ++i)
		printf("%d is %c\n", i , chars[i]);
	printf("chars is: %s\n", chars);

	free(chars);
	chars = NULL;

	return 0;
}
