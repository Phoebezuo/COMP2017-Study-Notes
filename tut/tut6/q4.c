#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_ELEMENTS (5)

struct scorecard {
    char name[20];
    int score;
};

int int_cmp(void* a, void* b) {
    int* a_int = a;
    int* b_int = b;
    return (*a_int - *b_int);
}

int str_cmp(void* a, void* b) {
    // type casting as a pointer to string
    char** a_ptr = a;
    char** b_ptr = b;
    char* a_str = *a_ptr;
    char* b_str = *b_ptr;

    // allow compare between different length
    while (*a_str || *b_str) {
        if (*a_str < *b_str) {
            return 1;
        } else {
            return -1;
        }
        a_str++;
        b_str++;
    }
    return 0;
}

int struct_cmp(void* a, void* b) {
    struct scorecard* a_struct = a;
    struct scorecard* b_struct = b;
    return (a_struct->score - b_struct->score);
}

void swap(void* xp, void* yp, size_t size_element) {
    void* temp = malloc(size_element);
    memcpy(temp, xp, size_element);
    memcpy(xp, yp, size_element);
    memcpy(yp, temp, size_element);
    free(temp);
}

void bubble_sort(void* element, size_t n_elements, size_t size_element, int (*cmp)(void*, void*)) {
    for (int i = 0; i < n_elements - 1; i++) {
        for (int j = 0; j < n_elements - 1; j++) {
            // void* compare one byte each
            if (cmp(element + j * size_element, element + (j + 1) * size_element) > 0) {
                swap(element + j * size_element, element + (j + 1) * size_element, size_element);
            }
        }
    }
}

int main() {
    int int_list[N_ELEMENTS] = {3, 4, 2, 6, 5};
    bubble_sort(int_list, N_ELEMENTS, sizeof(int), int_cmp);
    for (int i = 0; i < N_ELEMENTS; i++) {
        printf("%d ", int_list[i]);
    }
    puts("");


    char* str_list[N_ELEMENTS] = {"hello", "world", "2017", "pretty", "hard"};
    bubble_sort(str_list, N_ELEMENTS, sizeof(char*), str_cmp);
    for (int i = 0; i < N_ELEMENTS; i++) {
        printf("%s\n", str_list[i]);
    }

    struct scorecard a = {"phoebe", 300};
    struct scorecard b = {"edward", 200};
    struct scorecard c = {"lesi", 350};
    struct scorecard struct_list[3] = {a, b, c};
    bubble_sort(struct_list, 3, sizeof(struct scorecard), struct_cmp);
    for (int i = 0; i < 3; i++) {
        printf("%s %d\n", struct_list[i].name, struct_list[i].score);
    }

    return 0;
}
