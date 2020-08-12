#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void do_wc(FILE* f, const char* name) {
    
    int words = 0;
    int lines = 0;
    int bytes = 0;
    char c = 0;

    
    if(f != NULL) {
        
        int word_ev = 0;
        while((c = fgetc(f)) != EOF) {
            if(c == '\n') {
                lines++;
                if(word_ev > 0) {
                    words++;
                    word_ev = 0;
                }
            } else if(c == ' ') {
                if(word_ev > 0) {
                    words++;
                    word_ev = 0;
                }
            } else {
                word_ev++;
            }
            bytes++;
        }
        
        if(word_ev > 0) {
            words++;
        }
        printf("%d\t%d\t%d\t%s\n", lines, words, bytes, name);
    }
}

int main(int argc, char** argv) {
    if (argc > 1) {
        for(int i = 1; i < argc; i++) {
            FILE* f = fopen(argv[i], "r");
            if(f != NULL) {
                do_wc(f, argv[i]);
            }
            fclose(f);
        }
    } else {
        if(stdin != NULL) {
            do_wc(stdin, "stdin");
        }
    }
}
