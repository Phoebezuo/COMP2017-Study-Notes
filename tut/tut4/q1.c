#include <stdio.h>
#include <string.h>

typedef int uint8_t;
typedef int uint32_t;

struct quoll {
    char name[20];
    uint8_t age;
};

struct quokka {
    char * name;
    struct quokka * quokka_father;
    struct quokka * quokka_mother;
};

union mammal {
    struct quoll l;
    struct quokka a;
};

int main() {
    int a;
    int * b = &a;
    int * c = NULL;

    unsigned d;
    short e;
    long f;
    size_t g;
    long long h;

    uint8_t i;
    uint32_t j;

    printf("sizeof(int): %lu\n", sizeof(int)); // 4
    printf("sizeof(short): %lu\n", sizeof(short)); // 2
    printf("sizeof(long): %lu\n", sizeof(long)); // 8

    printf("sizeof(union mammal): %lu\n", sizeof(union mammal)); // 24
    printf("sizeof(struct quokka): %lu\n", sizeof(struct quokka)); // 24
    printf("sizeof(struct quoll): %lu\n", sizeof(struct quoll)); // 21

    printf("sizeof(struct quoll*): %lu\n", sizeof(struct quoll*)); // 8
    printf("sizeof(struct quokka*): %lu\n", sizeof(struct quokka*)); // 8
}
