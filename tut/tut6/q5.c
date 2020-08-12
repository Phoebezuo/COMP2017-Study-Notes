#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_ELEMENTS (5)

struct scorecard {
    char name[20];
    int score;
};

int int_cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int str_cmp(const void* a, const void* b) {
    // allow compare between different length
    while (*(*(char**)a) || *(*(char**)b)) {
        if (*(*(char**)a) < *(*(char**)b)) {
            return 1;
        } else {
            return -1;
        }
    }
    return 0;
}

int struct_cmp(const void* a, const void* b) {
    return (((struct scorecard*)a)->score - ((struct scorecard*)b)->score);
}

int main() {
    int int_list[N_ELEMENTS] = {3, 4, 2, 6, 5};
    qsort(int_list, N_ELEMENTS, sizeof(int), int_cmp);
    for (int i = 0; i < N_ELEMENTS; i++) {
        printf("%d ", int_list[i]);
    }
    puts("");


    char* str_list[N_ELEMENTS] = {"hello", "world", "2017", "pretty", "hard"};
    qsort(str_list, N_ELEMENTS, sizeof(char*), str_cmp);
    for (int i = 0; i < N_ELEMENTS; i++) {
        printf("%s\n", str_list[i]);
    }

    struct scorecard a = {"phoebe", 300};
    struct scorecard b = {"edward", 200};
    struct scorecard c = {"lesi", 350};
    struct scorecard struct_list[3] = {a, b, c};
    qsort(struct_list, 3, sizeof(struct scorecard), struct_cmp);
    for (int i = 0; i < 3; i++) {
        printf("%s %d\n", struct_list[i].name, struct_list[i].score);
    }


    return 0;
}
