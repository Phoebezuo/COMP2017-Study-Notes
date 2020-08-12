#include <stdio.h>
#include <stdlib.h>

void my_strcpy(void* dest, void* src, unsigned no_bytes) {
    int i = 0; // make sure we have terminator
    for (i = 0; i < no_bytes; i++) {
        char* d = dest;
        char* s = src;
        d[i] = s[i];
    }
    // dest[i] = '\0';
    // do not need terminator this time
}

int main() {
    char buf[50];
    int array[10];
    int garbage[] = { 1, 2, 3, 4, 5, 6 };

    my_strcpy(buf, "Hello World", 12);
    printf("%s\n", buf);

    my_strcpy(array, garbage, sizeof(garbage));
    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    puts("");
    return 0;
}
