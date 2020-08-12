#include <stdio.h>
#include <stdlib.h>
#include "iterator.h"
#include "linkedlist.h"

void iter_traverse(struct iterator* iter, void(*fn)(void*)) {
	if(iter) {
		void* element = NULL;
		while((element = iter->next(iter)) != NULL) {
			//Do something here
			fn(element);
		}
	}
}

void print_int(void* data) {
	int* p = (int*) data;
	printf("%d\n", *p);
}


int main() {
	printf("%lu %lu\n", sizeof(struct ll_node), sizeof(struct iterator));

	struct ll_node* head = NULL;
	for(int i = 0; i < 10; i++) {
		int* j = malloc(sizeof(int));
		*j = i;
		ll_append(&head, j);
	}

	struct iterator iter = { .cursor = head, .next = ll_next };
	iter_traverse(&iter, print_int);	
	ll_destroy(&head);

	return 0;
}
