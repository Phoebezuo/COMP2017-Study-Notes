#include <stdio.h>
#include <string.h>

int encode_run(const char* line_run, unsigned line_len, char* buf, unsigned int buf_len) {

    char c = line_run[0];
    int count = 0;
    int buf_index = 0;


    // Iterate through the line run
    for (int i = 0; i < line_len - 1; i++) { // Why (line_len - 1)?
        // Test if current character is different to prev
        if (c != line_run[i]) {
            buf[buf_index++] = '(';
            buf[buf_index++] = c;
            buf[buf_index++] = ',';
            // convert the count to a string (only works up to 9)
            buf[buf_index++] = (char)(count + '0');
            buf[buf_index++] = ')';
            // update pre char to current
            c = line_run[i];
            // restore count to 0, start new counting
            count = 0;
        }
        count++;
    }

    // account for the last sequence
    buf[buf_index++] = '(';
    buf[buf_index++] = c;
    buf[buf_index++] = ',';
    buf[buf_index++] = (char)(count + '0');
    buf[buf_index] = ')';
    // null terminate the output buffer
    buf[buf_index + 1] = '\0';
    return 0;
}

int decode_run(const char* tuples, unsigned len, char* buf, unsigned int buf_len) {

    int buf_index = 0;

    // Iterate through the line run
    for (int i = 0; i < len - 1; i += 5) {
        // Test if current character is different to prev
        if (tuples[i] == '(') {
            char value = tuples[i + 1];
            int n_repeat = tuples[i + 3] - '0';

            // Print number of repeats to output string
            for (int j = 0; j < n_repeat; j++) {
                buf[buf_index++] = value;
            }

        }
    }

    // null terminate the output buffer
    buf[buf_index] = '\0';

    return 0;
}

int main(int argc, char **argv) {
    char encoded_run[128];
    char output_line[128];

    encode_run("1122333334423", 14, encoded_run, 128);
    printf("%s\n", encoded_run); // (1,2)(2,2)(3,5)(4,2)(2,1)(3,1)
    decode_run(encoded_run, strlen(encoded_run), output_line, 128);
    printf("%s\n", output_line); // 1122333334423

    encode_run("1", 2, encoded_run, 128);
    printf("%s\n", encoded_run); // (1,1)
    decode_run(encoded_run, strlen(encoded_run), output_line, 128);
    printf("%s\n", output_line); // 1

    encode_run("123456", 7, encoded_run, 128);
    printf("%s\n", encoded_run); // (1,1)(2,1)(3,1)(4,1)(5,1)(6,1)
    decode_run(encoded_run, strlen(encoded_run), output_line, 128);
    printf("%s\n", output_line); // 123456
}
