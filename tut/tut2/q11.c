#include <stdio.h>
#include <string.h>
#define MAX_LEN 100

int string_compare(const char* w1, const char* w2, unsigned int len) {
    if (w1 == NULL || w2 == NULL)
        return -1;

    for (int i = 0; i < len; i++) {
        if(*w1 < *w2) { return -1; }
		if(*w1 > *w2) { return 1; }
		w1++;
		w2++;
    }
    return 0;
}

int main(int argc, char** argv) {
    if(argc != 2) {
		printf("Need more arguments\n");
		return 0;
	}

    // argv[0] is the name of file
	char* search_term = argv[1];
	int len = strlen(search_term);

	char buffer[MAX_LEN];

	while(fgets(buffer, sizeof(buffer), stdin) != NULL) {

        char* current_term = buffer;
        // stop util current term is null byte
		while(*current_term) {
            // two thing are exactly same before len
			if(string_compare(current_term, search_term, len) == 0)	{
				printf("Found: %s", buffer);
				break;
			}
			current_term++;
		}
	}
	return 0;
}
x
