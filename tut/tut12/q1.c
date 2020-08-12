#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

static inline bool is_palindrome(char * s, size_t len) {
    if (len <= 1) {
        return true; 
    } else if (s[0] != s[len - 1]) {
        return false; 
    } 
    return is_palindrome(s + 1, len - 2);
}

bool is_palindrome_iter(char* s, size_t len) {
    while (true) {
        if (len <= 1) {
            return true;
        } else if (s[0] != s[len - 1]) {
            return false;
        }
        s++;
        len -= 2;
    }
}

int main() {
    const clock_t tick = clock();

    int result = is_palindrome("noon", sizeof("noon")); 
    printf("noon is palindrome: True or False %d\n", result);

    result = is_palindrome("madam", sizeof("madam"));
    printf("madam is palindrome: True or False %d\n", result);

    result = is_palindrome("rececar", strlen("racecar"));
    printf("racecar is palindrome: True or False %d\n", result);

    result = is_palindrome("phoebe", strlen("phoebe"));
    printf("phoebe is palindrome: True or False %d\n", result);

    for (int i = 0; i < 100; i++) {
        char long_palindrome_recur[20001] = {0};

        for (int j = 0; j < 20000; j++) {
            long_palindrome_recur[j] = 'a';
        }

        result = is_palindrome(long_palindrome_recur, strlen(long_palindrome_recur));
    }

    const clock_t tock = clock();
    printf("Time elapsed: %fs\n", (double) (tock - tick) / CLOCKS_PER_SEC);
}