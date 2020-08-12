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
  unsigned int pad_1:1;
  unsigned int pad_2:1;
  unsigned int pad_3:1;
  unsigned int pad_4:1;
  float left;
  float right;
} gamepad_data;

typedef union {
	gamepad_data d;
	unsigned int raw[2];
} gdata;

//Start reading data is faking input to demonstrate what is happening
void read_gamepad(gdata* d) {
  d->raw[0] = rand();
  d->raw[1] = rand();
}

/*
 *
 */
int main(int argc, char** argv) {
  srand(time(NULL));
  int n = strtol(argv[2], NULL, 10);
  FILE* f = fopen(argv[1], "wb");	
  gdata u_data;
  if(f != NULL) {
	  while(n >= 0) {
	  	  n--;
		  read_gamepad(&u_data);
		  fwrite(&(u_data.d), sizeof(gamepad_data), 1, f);
		  //fflush(f);
		  sleep(1); //Updates every second
	  }
  }
  fclose(f);
  return 0;
}

