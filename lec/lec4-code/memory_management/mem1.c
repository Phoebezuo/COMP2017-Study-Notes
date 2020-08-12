#include <stdio.h>
#include <stdlib.h>

int main() {

	int *nums = NULL;
	
	nums = (int*)malloc(sizeof(int) * 10);
	int i;
	for (i = 0; i < 10; ++i) {
		nums[i] = 9990 + i;
		printf("%d: %d\n", i, nums[i]);
	}

	free(nums);

	nums = NULL;

	for (i = 0; i < 10; ++i) {
		printf("%d: %d\n", i, nums[i]);
	}


	return 0;
}
