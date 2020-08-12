#include <stdlib.h>

// initialise an n sized array of ints
void array_init_1(int n, int *nums) {
    if (n <= 0)
        return;
    int i = 0;
    for (i = 0; i < n; ++i)
        nums[i] = 1;
}

// initialise an n sized array of ints
void array_print(int n, int *nums) {
    if (n <= 0)
        return;
    int i = 0;
    for (i = 0; i < n; ++i)
        printf("%d ", nums[i]);
    printf("\n");
}

// create an return a n sized array of ints
int * array_new(int n) {
    int *tmp = (int*)malloc(sizeof(int) * n);
    if (tmp == NULL)
        ; // something terribly wrong

    return tmp;
}

int main()
{
    int *nums = array_new(10);
    
    array_print(nums);
    array_init_1(nums);
    array_print(nums);
    
    // never forget!
	free(nums);

	return 0;
}
