#include <stdio.h>

enum TYPE { FIRE, WATER, FLYING, ROCK, ELECTRIC };
struct pokemon {
    const char * name;
    enum TYPE type;
};

int main () {
    printf("sizeof(struct pokemon): %lu\n", sizeof(struct pokemon));
    struct pokemon pikachu = { "Pikachu", ELECTRIC };
    struct pokemon *ptr = &pikachu;
    ptr -> name = "Raichu";
    ptr -> type = ELECTRIC;
    printf("%s %d\n", ptr -> name, ptr -> type);
}
