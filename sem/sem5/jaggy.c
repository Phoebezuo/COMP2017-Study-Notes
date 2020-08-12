#include <stdio.h>
#include <stdlib.h>

/*

   We will be building a jagged array, this will
   be used to look into how dynamic memory works with
   nested pointers


*/

int main() {
	//Number of rows
	int lens[] = { 2, 4, 6, 10 };
	int** rows = malloc(sizeof(int*)*4);

	//Prints out the pointers
	for(int i = 0; i < 4; i++) {
		printf("%p\n", rows+i);
	}

	rows[0] = malloc(sizeof(int)*lens[0]);
	rows[1] = malloc(sizeof(int)*lens[1]);
	rows[2] = malloc(sizeof(int)*lens[2]);
	rows[3] = malloc(sizeof(int)*lens[3]);

	puts("Printing each malloc'd object");

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < lens[i]; j++) {
			*((*(rows+i))+j) = j+1;
		}
	}


	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < lens[i]; j++) {
			printf("%d ", rows[i][j]);
		}
		puts("");
	}



	//Not freeing the memory yet!


	for(int i = 0; i < 4; i++) {
		free(rows[i]);
	}
	free(rows);
}
