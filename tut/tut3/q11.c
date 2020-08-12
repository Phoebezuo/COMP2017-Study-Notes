#include <stdio.h>
#include <stdlib.h>
#define LOWER (33)
#define UPPER (126)


int main(int argc, char **argv) {
    int len = atoi(argv[1]);
    char result[len];
    srand(2);
    for (int i = 0; i < len; i++) {
        result[i] = (rand() % (UPPER - LOWER + 1)) + LOWER;
    }
    result[len] = '\0';
    puts(result);
}
