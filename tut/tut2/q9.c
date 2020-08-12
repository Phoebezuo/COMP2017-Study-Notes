#include <stdio.h>
#include <string.h>
#define MAX_LEN 100

int main(void) {
    // one extra byte needed for the null character 
    char buffer[MAX_LEN];
    
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // strlen do not include the null byte
        int len = strlen(buffer)-1;
        printf("%d\n",strlen(buffer));
        printf("%zu\n",sizeof(buffer));
        
        // Check for newline character
        // index of last character is len-1, as it starts from 0
        if (buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        for (int i = 0; i < len / 2; i++) {
            char tmp = buffer[i];
            buffer[i] = buffer[len - i - 1];
            buffer[len - i - 1] = tmp;
        }

        printf("%s\n", buffer);

    }

    return 0;
}

