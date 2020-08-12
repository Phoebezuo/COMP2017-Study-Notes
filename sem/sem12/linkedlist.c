#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "iterator.h"

void ll_append(struct ll_node** n, void* value) {
	if(n) {
		struct ll_node* p = malloc(sizeof(struct ll_node));
		p->next = NULL;
		p->element = value;
		if(*n) { //Head has been assigned
			struct ll_node* cursor = *n;
			while(cursor->next != NULL) {
				cursor = cursor->next;
			}
			cursor->next = p;
		} else {
			*n = p;
		}
	}
}

void ll_destroy(struct ll_node** n) {
	if(n) {
		struct ll_node* cursor = *n;
		
		while(cursor != NULL) {
			struct ll_node* temp = cursor->next;
			free(cursor->element);
			free(cursor);
			cursor = temp;
		}
		
	}
}

void* ll_next(void* iter) {
	if(iter) {
	
		struct iterator* i = (struct iterator*) iter;
		void* v = NULL;
		if(i->cursor) {
			struct ll_node* n = (struct ll_node*) i->cursor;
			
			v = n->element;
			n = n->next;
			i->cursor = n;
			
		}
		return v;
	} else {
		return NULL;
	}
}

