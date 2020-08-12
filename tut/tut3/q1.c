#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define BUF_SIZE (100)

int main(void) {
    int c;
    int e;

    while ((c=getchar()) != EOF) {
        if (c >= 'a' && c <= 'z') {
            e = c - 32;
            putchar(e);
        } else {
            putchar(c);
        }
    }
    
    // method two 
    // char buf[BUF_SIZE];
    // while (fgets(buf, BUF_SIZE, stdin) != NULL) {
        // for (char *p = buf; *p; ++p)
            // if (*p >= 'a' && *p <= 'z')
                // *p = toupper(*p); // or *p -= ('a' - 'A')
    
        // printf("%s\n", buf);
    // }

    return 0;
}
