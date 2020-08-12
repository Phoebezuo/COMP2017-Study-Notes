#include <stdio.h>
#include <stdlib.h>

int main() {

    void *a = malloc(sizeof(int*) * (1 << 3));
    void *b = malloc(sizeof(int*) * 9);

    for (size_t i = 0; i <= 6; i++) {
        ((int*)a)[5] += i >> 1;
        ((size_t*)b)[i] = i + ~i;

        // if (i == 8) {
        //     free(a);
        // }
    }
    free(a);
    free(b);
    return 0;
    // return ((int*)a)[0];
}
