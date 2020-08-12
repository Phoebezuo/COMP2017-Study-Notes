#include <stdio.h>
#include <stdlib.h>

int main() {

	int *nums;
	nums = (int*)malloc(10);
	if ( nums == NULL) {
		/// ...
		return 1;
	}

	int i;
	for (i = 0; i < 10; ++i)
		nums[i] = i+1;

	for (i = 0; i < 10; ++i)
		printf("%d is %d\n", i , nums[i]);

	free(nums);
	nums = NULL;

	return 0;
}
