#include <stdio.h>
#define ARRAY_LEN (5)

// calculate the average of an int array
float average(int* arr, unsigned int len){
    float sum = 0;
    for(int i = 0; i < len; i++){
        sum += arr[i];
    }
    return sum / len;
}

int main(){
    int arr[] = {1, 2, 3, 4, 50};
    printf("%f\n", average(arr, ARRAY_LEN)); // 12
    printf("%f\n", average(arr, 4)); // 2.5
    printf("%f\n", average(arr+2, 2)); // 3.5
    return 0;
}
