#include <stdio.h>
#include <string.h>

int main() 
{
	struct item {
		char barcode[6];
		const char *name;
		float price;	
	};	

	struct item tomatoes;
	printf("sizeof(struct item): %zu\n", sizeof(struct item));
	printf("sizeof(tomatoes): %zu\n", sizeof(tomatoes));
	
	struct item *tincan;
	printf("sizeof(struct item *): %zu\n", sizeof(struct item*));
	printf("sizeof(tincan): %zu\n", sizeof(tincan));
	
	tincan = NULL;
	printf("sizeof(peaches): %zu\n", sizeof(tincan));

	tincan = &tomatoes;
	printf("sizeof(peaches): %zu\n", sizeof(tincan));
	
	printf("sizeof(tomatoes.barcode): %zu\n", sizeof(tomatoes.barcode));
	printf("sizeof(tincan->barcode): %zu\n", sizeof(tincan->barcode));

	printf("sizeof(tomatoes.name): %zu\n", sizeof(tomatoes.name));
	printf("sizeof(tincan->name): %zu\n", sizeof(tincan->name));

	tomatoes.name = "The Greatest Tomatoes in a can";
	printf("sizeof(tomatoes.name): %zu\n", sizeof(tomatoes.name));
	printf("strlen(tomatoes.name): %zu\n", strlen(tomatoes.name));
	
	tomatoes.name = "TGT";
	printf("sizeof(tomatoes.name): %zu\n", sizeof(tomatoes.name));
	printf("strlen(tomatoes.name): %zu\n", strlen(tomatoes.name));
	
	printf("sizeof(tomatoes.price): %zu\n", sizeof(tomatoes.price));
	printf("sizeof(tincan->price): %zu\n", sizeof(tincan->price));
	
	// pointer arithmetic
	printf("tomatoes: %p\n", &tomatoes);
	printf("tomatoes barcode: %zu\n", (void*)&(tomatoes.barcode) - (void*)&tomatoes);
	printf("tomatoes name: %zu\n", (void*)&(tomatoes.name) - (void*)&tomatoes);
	printf("tomatoes price: %zu\n", (void*)&(tomatoes.price) - (void*)&tomatoes);
	
	return 0;
}