#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	We will be building a stack data structure
	This will be used push and pop data from the stack
	and will be backed by a linked list.

*/



struct stack_node {
	struct stack_node* next;
	void* data;
};


struct stack {
	struct stack_node* top;
	size_t len;
};


struct stack* stack_init() {
	struct stack* s = malloc(sizeof(struct stack));
	s->top = NULL;
	s->len = 0;
	return s;
}


void* stack_pop_object(struct stack* s);

void stack_push_copy(struct stack* s, void* data, size_t nbytes) {

	if(s == NULL || data == NULL || nbytes == 0) { return; };

	struct stack_node* new_node = malloc(sizeof(struct stack_node));
	new_node->data = malloc(nbytes);
	memcpy(new_node->data, data, nbytes);
	new_node->next = NULL;
	struct stack_node* current_top = s->top;
	s->top = new_node;
	s->top->next = current_top;

}

void stack_free(struct stack* s) {
	if(s != NULL) {
		void* n = NULL;
		while( (n = stack_pop_object(s)) != NULL) {
			free(n);
		}
	}
	free(s);
}


void* stack_pop_object(struct stack* s) {
	if(s != NULL) {
		//Not checking if top == NULL
		if(s->top != NULL) {
			struct stack_node* node = s->top;
			s->top = s->top->next;
			void* d = node->data;
			free(node);
			return d;
		}

	}
	return NULL;
}

struct my_data {
	int x;
	long y;
};


int main() {

	struct stack* s = stack_init();
	struct my_data data = { 1, 5 };

	stack_push_copy(s, &data, sizeof(struct my_data));

	data.x = 2;
	data.y = 10;

	stack_push_copy(s, &data, sizeof(struct my_data));

	data.x = 8;
	data.y = 90;

	stack_push_copy(s, &data, sizeof(struct my_data));

	data.x = 4;
	data.y = 20;


	stack_push_copy(s, &data, sizeof(struct my_data));

	data.x = 5;
	data.y = 20;

	stack_push_copy(s, &data, sizeof(struct my_data));

	void* n = NULL;

	while( (n = stack_pop_object(s)) != NULL) {
		struct my_data* d = (struct my_data*) n;
		printf("%d %ld\n", d->x, d->y);
		free(n);
	}

	stack_free(s);
	return 0;
}
