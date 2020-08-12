#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

/*
We want to firstly create a method to generate firmware files
even if the data is garbage

magic: 4bytes, unsigned integer
timestamp: 4bytes, integer
author: 4bytes, char array
crc: 4bytes, unsigned integer.
*/


extern uint32_t crc32(uint32_t crc, const char* buf, size_t len);

struct firmware_header {
	unsigned int magic;
	int timestamp;
	char author[4];
	unsigned int crc; 
};

#define N_PARTITIONS (12)
#define FIRMWARE_MAGIC (60232)


int main(int argc, char** argv) {

	if(argc > 1) {

		struct firmware_header header;
		FILE* file = fopen(argv[1], "w");
		int array[64*N_PARTITIONS];
		
		srand(time(NULL));

		for(int i = 0; i < 64*N_PARTITIONS; i++) {
			array[i] = rand();
		}		
		
		unsigned int crcval = crc32(0, (char*) array, (64*N_PARTITIONS)*sizeof(int));

		header.magic = FIRMWARE_MAGIC;
		header.timestamp = time(NULL);
		strcpy(header.author, "JSH");
		header.crc = crcval;


		fwrite(&header, sizeof(struct firmware_header), 1, file);
		fwrite(array, sizeof(int), (64*N_PARTITIONS), file);

		fclose(file);
		
	}
}




