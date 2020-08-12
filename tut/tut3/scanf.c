#include <stdio.h>

int main(void) {
    int x;
    double y;
    // buffer is an array and has type char[20]
    char buffer[20];

    // scanf function returns the number of input items successfully matched and assigned
    if (scanf("%d %lf %19s", &x, &y, buffer) != 3) {
        // when reading strings with scanf, you should provide a width specifier 
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    printf("%d %f %s\n", x, y, buffer);
    return 0;
}
