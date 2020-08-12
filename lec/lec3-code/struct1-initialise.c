#include <stdio.h>
#include <string.h>

struct item {
	char barcode[6];
	const char *name;
	float price;	
};

// function prototype
float items_sum( struct item *items, size_t n );

// initialise a structure with values
// pass in the memory address of structure
// Warning: assume name has preallocated memory
void item_init( struct item *item, 
	const char *barcode, const char *name, float price) {

	if (item == NULL || 
		barcode == NULL || 
		name == NULL)
		return; // raise an error?
		
	strncpy(item->barcode, barcode, 6);
	item->name = name; // warning
	item->price = price;
}

int main() {
	// create array
	struct item items[2];

	// initialise elements
	item_init( &(items[0]), "DFH291", "Big tuna", 1.25);
	item_init( &(items[1]), "FGD135", "Tin can", 3.50);
	
	float sum = items_sum(items, 2);
	printf("sum: %.2f\n", sum);
	
	return 0;
}




// sum all prices
float items_sum( struct item *items, size_t n ) {
    float sum = 0;
    
    int i = 0;
    for ( ; i < n; ++i) {
        sum += items[i].price;
    }
    return sum;
}
