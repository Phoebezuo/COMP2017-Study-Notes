#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct {
  unsigned int id:8;
  unsigned int locked:8;
  unsigned int x:1;
  unsigned int y:1;
  unsigned int z:1;
  unsigned int w:1;
  unsigned int a:1;
  unsigned int b:1;
  unsigned int c:1;
  unsigned int d:1;
  unsigned int l:1;
  unsigned int r:1;
  unsigned int st:1;
  unsigned int sel:1;
} gamepad_data;


void print_components(gamepad_data* data) {
	printf("%u %u %u %u %u %u %u %u %u %u %u %u %u %u %u\n", 
		data->id, data->locked, data->x, data->y, data->y, data->z, data->w,
		data->a, data->b, data->c, data->d, data->l, data->r, data->st, data->sel);


}


/*
 *
 */
int main(int argc, char** argv) {
  srand(time(NULL));
  FILE* f = fopen(argv[1], "r");	
  int n_pkts = strtol(argv[2], NULL, 10);
  gamepad_data data;
  if(f != NULL) {
  	for(int i = 0; i < n_pkts; i++) {
		fread(&data, sizeof(gamepad_data), 1, f);
		print_components(&data);
	}
  }
  fclose(f);
  return 0;
}
