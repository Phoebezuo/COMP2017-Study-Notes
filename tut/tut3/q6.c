#include <stdio.h>
#include <math.h>

int main() {
    int r;
    // const float PI = 3.1415;
    printf("Specify the radius of the sphere: ");
    scanf("%d", &r);
    double v = 4/3 * M_PI * pow(r,3);
    printf("Volume is: %f\n", v);
}
