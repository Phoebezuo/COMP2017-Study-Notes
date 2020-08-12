#include <stdio.h>

int main(int argc, char **argv) {
    char *greeting = argv[1];
    char name[20];
    printf("What is your name? ");
    // scanf("%s", name);
    fgets(name, 100, stdin);
    printf("%s! %s", greeting, name);
    return 0;
}

