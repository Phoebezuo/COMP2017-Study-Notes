#include <stdio.h>

// idiom
// find the first occurrence of f(x) == TRUE
// where f(x) = (x % 2 == 0)
// return the *both* the value and the index

struct pair {
	int value;
	int index;
};

// if no data then return -1 index;
struct pair get_best_index(int *data, size_t n) {

	struct pair pair;

	pair.index = -1;
	pair.value = -1;
	
	if (data == NULL || n <= 0) {
		return pair;
	}

	pair.index = 0;
	pair.value = data[0];
	
	int i;
	for (i = 0; i < n; i++)  {
		v = data[i];
		if ( v % 2 == 0 ) {
			pair.value = v;
			pair.index = i;
			break;
		}
	}

	return pair; // copy operation
}

int main()
{

	return 0;
}
