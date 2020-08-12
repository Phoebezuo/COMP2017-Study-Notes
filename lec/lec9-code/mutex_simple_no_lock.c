#include <stdio.h>
#include <string.h>
#include <pthread.h>

char *message = "Chocolate microscopes?";
int mindex = 0;
size_t message_len = 0;

pthread_t my_thread;

void* threadF(void *arg) {
  while (1) {
    if (mindex < message_len) {
      printf("%c", message[mindex]);
      mindex++;
    } else
      break;
  }
  printf("Thread ended at %d.\n", mindex);
  return NULL;
}

int main(void) {
  message_len = strlen(message);
  pthread_create(&my_thread,NULL,threadF,NULL);

  while (1) {
    if (mindex < message_len) {
      printf("%c", message[mindex]);
      mindex++;
    } else {
        break;
    }
  }
  printf("main ended at %d.\n", mindex);
  pthread_join(my_thread, NULL);
  printf("\n");
  printf("all threads ended: %d.\n", mindex);
  return 0;
}
