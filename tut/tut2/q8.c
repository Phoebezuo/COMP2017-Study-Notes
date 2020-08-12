#include <stdio.h>
#include <string.h> // allow you to use sizeof

int atoi (const char s[]) {
    int result = 0;
    int multiplier = 1;
    
    // check the first sign
    if (s[0] == '-') {
        multiplier = -1;
        s++;
    }
    // get the size of array in function, you can find the null byte 
    while (*s) { // only null byte is false 
        result = result * 10 + (*s - '0');
        s++;
    }
    
    return result * multiplier;
}

int main(void) {
    printf("%d\n", atoi(""));
    printf("%d\n", atoi("0"));
    printf("%d\n", atoi("0123"));
    printf("%d\n", atoi("1234"));
    printf("%d\n", atoi("-1234"));
}
