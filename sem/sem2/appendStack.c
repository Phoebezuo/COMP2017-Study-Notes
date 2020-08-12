#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// append string to another #ifndef
char* append_stack(char* base, char* str){
    // get the length of base
    int base_len = 0;
    char* cur = base;
    while(*cur){
        base_len++;
        cur++;
    }

    // get the length of str
    int str_len = 0;
    cur = str;
    while(*cur){
        str_len++;
        cur++;
    }

    char result = [base_len + str_len + 1];
    for (int i = 0; i < base_len; i++) {
        result[i] = base[i];
    }
    for (int i = 0; i < str_len; i++) {
        result[base_len + i] = str[i];
    }

    return result;
}

int main(){
    char array[50] = "Hello, ";

    // change the rest in rest to 1
    for (int i = strlen(array) + 1; i < 50; i++) {
        array[i] = 1;
    }

    char* result1 = append_stack(array, "World!");
    char* result2 = append_stack(array, "123");
    printf("%s\n", result1); // Hello, Wor123
    return 0;
}
