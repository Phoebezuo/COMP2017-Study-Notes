#include <stdio.h>
#include <stdlib.h>

struct list {
	int data;
	struct list *next;
};

int main() {
	struct list *cursor;
	struct list *a;
	struct list *b;
	struct list *c;

	a = (struct list*)malloc(sizeof(struct list));
	b = (struct list*)malloc(sizeof(struct list));
	c = (struct list*)malloc(sizeof(struct list));

	a->data = 'a';
	a->next = NULL;

	b->data = 'b';
	b->next = c;

	c->data = 'c';
	c->next = NULL;

	cursor = b;

	printf("cursor is at : %c\n", cursor->data);
	printf("cursor addr is : %p\n", cursor);
	printf("cursor->next addr is : %p\n", cursor->next);

	cursor = a;
	
	printf("cursor is at : %c\n", cursor->data);
	printf("cursor addr is : %p\n", cursor);
	printf("cursor->next addr is : %p\n", cursor->next);

	a->next = b;

	printf("cursor is at : %c\n", cursor->data);
	printf("cursor addr is : %p\n", cursor);
	printf("cursor->next addr is : %p\n", cursor->next);

	return 0;
}
