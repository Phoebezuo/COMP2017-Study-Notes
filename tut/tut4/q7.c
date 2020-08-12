#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE* file1 = fopen(argv[1],"r");
    if (file1 == NULL) {
        perror("file1 not exist");
        return 1;
    }
    FILE* file2 = fopen(argv[2],"r+");
    if (file2 == NULL) {
        perror("file2 not exist");
        return 1;
    }

    char buffer[1000];
    char words[20][50];
    while (fgets(buffer, 1000, file1) != NULL) {
        int word_idx = 0;
        int letter_idx = 0;
        for (int i = 0; i <= strlen(buffer); i++) {
            if (buffer[i] == ' ' || buffer[i] == '\0') {
                words[word_idx][letter_idx] = '\0';
                word_idx++; // for next word
                letter_idx = 0; // for next word, init index to 0
            } else {
                words[word_idx][letter_idx] = buffer[i];
                letter_idx ++;
            }
        }
        for (int i = 0; i <= word_idx; i++) {
            printf("%s\n", words[i]);
            if (strcmp(words[i], "Always") == 0) {
                fprintf(file2, "%s", "Never");
            } else {
                fprintf(file2, "%s", words[i]);
            }
            puts("");
        }
    }
    fclose(file1);
    fclose(file2);
}
