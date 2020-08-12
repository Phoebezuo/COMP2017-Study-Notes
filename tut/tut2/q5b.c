#include <stdio.h>

int main(int argc, char** argv) {
    int x[] = { 1, 2, 3 };
    int * p1 = x;
    int * p2 = x + 1;
    printf("%zu %zu\n", sizeof(x[0]), sizeof(x));
    printf("p1 value, p2 value: %d %d\n", *p1, *p2);
    printf("p1 value with offset: %d\n", *(p1 + 1));
    printf("p2 value with offset: %d\n", *(p2 - 1));
    printf("p1 value plus scalar: %d\n", (*p1) + 2);
    printf("p1 plus offset followed: %d\n", *(p1 + 2));
    printf("p1 plus offset followed: %d\n", p1[2]);
    return 0;
}
