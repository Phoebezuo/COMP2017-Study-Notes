#include <stdio.h>
#include <stdlib.h>

int var_a;

int sum (const int* var_b) {
    static int var_c;
    var_c += *var_b;
    return var_c;
}

int main(int argc, char** argv) {
    int var_d = 0;

    int* var_e = malloc(sizeof(int));
    if (NULL == var_e) {
        perror("Malloc Failed!");
        return 1;
    }
    *var_e = 2;
    sum(&var_d);
    sum(&var_a);
    sum(var_e);
    char* var_f = calloc(sizeof(char), 100);
    if (NULL == var_f) {
        perror("Calloc Failed");
        return 1;
    }

    free(var_e);
    return 0;
}
