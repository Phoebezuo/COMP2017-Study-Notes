#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 4

typedef struct pokemon {
    char name[100];
    unsigned level;
} pokemon;

int main(void) {
    pokemon pokemons[SIZE] = {
        { .name = "Pikachu", .level = 5 },
        { .name = "Squirtle", .level = 10 },
        { .name = "Charizard", .level = 50 },
        { .name = "Eevee", .level = 25 }
    };

    printf("sizeof(size_t) = %zu\n", sizeof(size_t)); // 8
    printf("sizeof(unsigned) = %zu\n", sizeof(unsigned)); // 4
    printf("sizeof(char[100]) = %zu\n", sizeof(char[100])); // 100

    printf("sizeof(pokemon) = %zu\n", sizeof(pokemon)); // 104
    printf("sizeof(pokemons) = %zu\n", sizeof(pokemons)); // 416

    // attempt to save to file
    FILE* file = fopen("pokemon.dex", "w");
    if (file == NULL) {
        perror("unable to open file for writing");
        return 1;
    }
    fwrite(pokemons, sizeof(pokemon), SIZE, file);
    fclose(file);

    // read from file
    FILE* f = fopen("pokemon.dex", "r");
    fread(pokemons, sizeof(pokemon), SIZE, f);

    for (size_t i = 0; i < SIZE; i++) {
        printf("Name: %s Level: %d\n", pokemons[i].name, pokemons[i].level);
    }
    return 0;
}
