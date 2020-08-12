#include <stdio.h>
#include <time.h>

int main(void) {
    const clock_t tick = clock(); 

    int ops = 0;
    for (int i = 0; i < 100000000; i++) {
        ops += i;
    }

    const clock_t tock = clock();
    printf("Time elapsed: %fs\n", (double) (tock - tick) / CLOCKS_PER_SEC);
    return 0; 
}