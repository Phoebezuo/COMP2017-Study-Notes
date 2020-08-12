#include <stdlib.h>
#include <stdio.h>
#include "rbuf.h"

rbuf_queue* rbuf_new(size_t cap) {
	rbuf_queue* q = malloc(sizeof(rbuf_queue));
	q->cursor = 0;
	q->capacity = cap;
	q->size = 0;
	q->elements = malloc(sizeof(void*)*cap);
	return q;
}

void rbuf_enqueue(rbuf_queue* q, void* element) {
	if(q->size >= q->capacity) {
		//Resize
		q->elements = realloc(q->elements, sizeof(void*)*q->capacity*2);
		q->capacity = q->capacity * 2;
	}
	q->elements[(q->cursor+q->size)%q->capacity] = element;
	q->size++;
}

void* rbuf_deque(rbuf_queue* q) {
	void* element = q->elements[q->cursor];
	q->cursor = (q->cursor+1) % q->capacity;
	return element;
}

void rbuf_delete(rbuf_queue* q, void(*cleanup(rbuf_queue*))) {
	if (cleanup != NULL) {
		cleanup(q);
	}
	free(q->elements);
	free(q);
}
