#include "rbuf.h"

int main() {
	int* n = malloc(sizeof(int));
	*n = 5;
	rbuf_queue* q = rbuf_new(10);
	rbuf_enqueue(q, n);
	int* p = rbuf_deque(q);
	rbuf_delete(q, NULL);
	free(n);
	return 0;
}
