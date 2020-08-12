#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct batsman {
    char first_name[20];
    char last_name[20];
    int score;
};

int output_scores(struct batsman* batters, const char* filename) {
    FILE* f = fopen(filename, "a");
    if (f != NULL) {
        fprintf(f, "%s, %s, %d\n", batters -> first_name, batters -> last_name, batters -> score);
    }
    return 0;
}

int main() {
    struct batsman b;
    strcpy(b.first_name, "Phoebe");
    strcpy(b.last_name, "Zuo");
    b.score = 20;

    // struct batsman* p = malloc(sizeof(struct batsman));

    output_scores(&b, "batters.csv");
    return 0;
}
