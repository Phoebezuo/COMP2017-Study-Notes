#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>


struct ll_node {
	struct ll_node* next;
	void* element;
};

void ll_append(struct ll_node** n, void* value);

void ll_destroy(struct ll_node** n);

void* ll_next(void* iter);
#endif
