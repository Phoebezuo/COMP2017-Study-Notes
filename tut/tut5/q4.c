#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buff[16];
    char* string = malloc(32);
    size_t len = 0;
    size_t capacity = 32;
    while (fgets(buff, 16, stdin)) {
        // if the length is exceed with the length
        if (len + 16 >= capacity) {
            // resize
            char* temp = realloc(string, capacity * 2); // return true or false
            if (temp) {
                string = temp;
                capacity *= 2;
            }
        }
        size_t l = strlen(buff);
        // copy 16 bytes from buff to "string + len"
        memcpy(string + len, buff, 16);
        len += l;
    }
    puts(string);
    return 0;
}
