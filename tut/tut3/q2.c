#include <stdio.h>
#define LENGTH 100

int main(void) {
    int velocity;
    double time;
    printf("What is your current km/h: ");
    scanf("%d", &velocity);

    printf("How many hours are you travelling for: ");
    scanf("%lf", &time);

    double distance = velocity * time;
    double convert_d = distance / 1.60934;
    double convert_v = velocity * 0.621371;


    printf("You will cover: %.2f km (%.2f mi)\nWhile travelling at %d km/h (%.2f mph)\n", distance, convert_d, velocity, convert_v);
}
