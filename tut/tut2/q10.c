#include <stdio.h>

int string_compare(const char* w1, const char* w2, unsigned int len) {
    if (w1 == NULL || w2 == NULL)
        return -1;

    for (int i = 0; i < len; i++) {
        if(*w1 < *w2) {
			return -1;
		}
		if(*w1 > *w2) {
			return 1;
		}

		w1++;
		w2++;
    }

    return 0;
}

int main()
{
	printf("%d\n", string_compare("comp2017", "comp2017", 8)); //0
	printf("%d\n", string_compare("pointers", "points", 6)); // -1
	printf("%d\n", string_compare("arreys", "arrays", 5)); // 1
    printf("%d\n", string_compare("arreys", "arrays", 3)); // 0
	return 0;
}
