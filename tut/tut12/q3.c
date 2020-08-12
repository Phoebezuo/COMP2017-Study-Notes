#include <stdio.h>
#include <stdlib.h>

void cpy1 (char* restrict dest, char* restrict src, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        dest[i] = src[i];
    }
}

void cpy2 (char* dest, char* src, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        dest[i] = src[i];
    }
}

// this will result in a segmentation fault because "123456" is a const char* 
void example1() {
    char* s = "123456";
    cpy2(s + 1, s, 4);
    printf("%s\n", s);
}

// the content of s will e 111116
void example2() {
    char s[] = "123456";
    cpy2(s + 1, s, 4);
    printf("%s\n", s);
}

int main() {
    // example1();
    example2();
}