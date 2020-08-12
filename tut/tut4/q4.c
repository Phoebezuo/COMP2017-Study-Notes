#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

// read by char
int main(int agrc, char* argv[]) {
    FILE* file = fopen("output1.txt", "r");
    if (file == NULL) {
        perror("unable to open file");
        fclose(file);
        return 1;
    }
    while (!feof(myfile)) {
        char ch = fgetc(myfile);
        printf("%c", ch-2 );
    }
    fclose(file);
    return 0;
}

// read by word
int main (int argc, char* argv[]) {
    FILE* file = fopen("output2.txt", "r+");
    if (file == NULL) {
        perror("unable to open file");
        fclose(file);
        return 1;
    }
    char str[100];
    while (fscanf(myfile, "%s", str) != EOF) {
        printf("%s\n", str);
    }
    fclose(file);
    return 0;
}

// read by line
int main (int argc, char* argv[]) {
    FILE* file = fopen("output3.txt", "r+");
    if (file == NULL) {
        perror("unable to open file");
        fclose(file);
        return 1;
    }
    char str[100];
    while (fgets(buffer, sizeof(buffer), nyfile) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
    return 0;
}
