#include <stdio.h>

int main(void) {
    printf("%-3s %-15s %-5s\n", "ID", "Name", "Score");
    const char* format = "%03d %-15s %.2f\n";

    printf(format, 1, "Bryan Cantrill", 99.449);
    printf(format, 2, "Scott Forstall", 99.999);

    return 0;
}
