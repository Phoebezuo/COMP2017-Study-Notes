#include <stdio.h>

int encode_run(const char* line_run, unsigned line_len, char* buf, unsigned int buf_len) {

    char c = line_run[0];
    int count = 0;
    int buf_index = 0;

    // Iterate through the line run
    for (int i = 0; i < line_len - 1; i++) { // Why (line_len - 1)?
        // Test if current character is different to prev
        if (c != line_run[i]) {
            // convert the count to a string (only works up to 9)
            buf[buf_index++] = (char)(count + '0');
            // update pre char to current
            c = line_run[i];
            // restore count to 0, start new counting
            count = 0;
        }
        count++;
    }

    // account for the last sequence
    buf[buf_index] = (char)(count + '0');
    // null terminate the output buffer
    buf_index = buf_index + 1;
    buf[buf_index] = '\0';
    return 0;
}

int main(int argc, char **argv) {
    char encoded_run[128];

    encode_run("1122333334423", 14, encoded_run, 128);
    printf("%s\n", encoded_run); // 225211

    encode_run("1", 2, encoded_run, 128);
    printf("%s\n", encoded_run); // 1

    encode_run("123456", 7, encoded_run, 128);
    printf("%s\n", encoded_run); // 111111
}
