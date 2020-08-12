#include <stdio.h>

int main(int argc, char** argv) {
    const char * ptr = "hello";
    printf("ptr: %s\n", ptr);

    const char array[] = "hello";
    printf("array: %s\n", array);

    const char array2[] = { 'h', 'e', 'l', 'l', 'o' };
    printf("array2: %s\n", array2);

    const char array3[] = { 'h', 'e', 'l', 'l', 'o', '\0' };
    printf("array3: %s\n", array3);

    const char array4[5] = { 'h', 'e', 'l', 'l', 'o' };
    printf("array4: %s\n", array4);

    const char array5[6] = { 'h', 'e', 'l', 'l', 'o', 0 };
    printf("array5: %s\n", array5);

    const char array6[20] = { 'h', 'e', 'l', 'l', 'o' };
    printf("array6: %s\n", array6);

    const char array7[20] = { 0 };
    printf("array7: %s\n", array7);

    const char array8[20] = "hello";
    printf("array8: %s\n", array8);

    printf("\nsizes\n");
    printf("ptr: %zu array: %zu\n", sizeof(ptr), sizeof(array));
    printf("array2: %zu array3: %zu\n", sizeof(array2), sizeof(array3));
    printf("*ptr: %zu &array: %zu\n", sizeof(*ptr), sizeof(&array));
    printf("&array2: %zu &array3: %zu\n", sizeof(&array2), sizeof(&array3));

    return 0;
}
