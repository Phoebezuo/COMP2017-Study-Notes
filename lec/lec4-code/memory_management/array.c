#include <stdlib.h>

// lifetime of memory and where does it exist?

int nums_global[10];

void foo() {
    int nums_local[10];

    return ;
}

int main() 
{
    foo();
    
	int *other_nums = (int*)malloc(sizeof(int) * 10);

	free(other_nums);

	return 0;
}
