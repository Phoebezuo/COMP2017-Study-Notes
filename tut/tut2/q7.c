#include <stdio.h>

void swap(int a[], int b[]) {
    int temp = *a;
    *a = *b; // swap the value on the address
    *b = temp;
}

int main(void) {
    int a = 2; 
    int b = 3; 
    swap(&a, &b); // swap the value on the address
    printf("%d %d\n", a, b);
    return 0;
}
