#include <stdio.h>
#include <stdlib.h>

struct list {
	int data;
	struct list *next;
};

int main() {

	struct list *cursor;

	cursor = (struct list*)malloc(sizeof(struct list));

	cursor->data = 'b';
	cursor->next = (struct list*)malloc(sizeof(struct list));

	struct list *tmp = cusor->next;
	tmp->data = 'c';
	tmp->next = NULL;

	struct list *a = (struct list*)malloc(sizeof(struct list));
	a.data = 'a';
	
	// correct
	a->next = cursor;
	cursor = a;
	
	// incorrect
	cursor = a;
	a->next = cursor;

	return 0;
}


