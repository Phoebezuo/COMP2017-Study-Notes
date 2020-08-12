#include <stdlib.h>

typedef struct rbuf_queue rbuf_queue;

struct rbuf_queue {
	size_t capacity;
	size_t size;
	size_t cursor;
	void** elements;
};

rbuf_queue* rbuf_new(size_t cap);

void rbuf_enqueue(rbuf_queue* q, void* element);

void* rbuf_deque(rbuf_queue* q);

void rbuf_delete(rbuf_queue* q, void(*cleanup(rbuf_queue*)));
