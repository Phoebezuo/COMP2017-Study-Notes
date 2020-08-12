#include <stdio.h>

#define ADD (0)
#define SUB (1)
#define MUL (2)
#define DIV (3)

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int div(int a, int b) { return a / b; }

int main() {
    int (*operation[])(int, int) = {add, sub, mul, div};
    int result = (*operation[ADD])(9, 10); // 19
    result = (*operation[SUB])(result, 10); // 9
    result = (*operation[MUL])(3, result); // 27
    result = (*operation[DIV])(result, 1); // 27
    printf("%d\n", result); // 27
    return 0;
}
