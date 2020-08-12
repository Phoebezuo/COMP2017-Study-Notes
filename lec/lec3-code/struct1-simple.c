#include <stdio.h>
#include <string.h>

struct item {
	char barcode[6];
	const char *name;
	float price;	
};

// memory input
// given an array of structs

// idiom
// sum all prices
float items_sum( struct item *items, int n )
{
	float sum = 0;
	
	int i = 0;
	for ( ; i < n; ++i) {
		sum += items[i].price;
	}
	return sum;
}

int main()
{
	// create array
	struct item items[2];

	// initialise elements
	// man strncpy - see warning
	strncpy(items[0].barcode, "DFH291", 6);
	items[0].name = "Big tuna";
	items[0].price = 1.25;
	
	//  init each field (man strncpy)
	strncpy(items[1].barcode, "FGD135", 6);
	items[1].name = "Tin can";
	items[1].price = 3.50;
	
	float sum = items_sum(items, 2);
	printf("sum: %.2f\n", sum);
	
	return 0;
}