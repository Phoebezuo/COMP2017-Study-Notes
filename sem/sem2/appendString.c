#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// append string to another #ifndef
void append_string(char* base, char* str){
    // get the len of base
    int base_len = 0;
    char* cur = base;
    // iterate through the string
    // null terminator correspond to zero
    while(*cur){
        base_len++;
        cur++;
    }

    // append str to base
    cur = str;
    int str_len = 0;
    while(*cur){
        base[base_len + str_len] = *cur;
        str_len++;
        cur++;
    }
    // indicate where to terminate
    base[base_len + str_len] = '\0';
}

int main(){
    char array[50] = "Hello, ";

    // change the rest in rest to 1
    for (int i = strlen(array) + 1; i < 50; i++) {
        array[i] = 1;
    }
    // strlen not include null terminator
    printf("%lu\n", strlen(array)); // 7

    append_string(array, "World!");
    printf("%s\n", array); // Hello, World!

    printf("%lu\n", strlen(array)); // 13
    return 0;
}
