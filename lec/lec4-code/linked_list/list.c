#include <stdio.h>

struct list {
	int data;
	struct list *next;
};

int main() {

	struct list *cursor;

	struct list a, b, c;

	printf("addr of a is: %p\n", &a);
	printf("addr of b is: %p\n", &b);
	printf("addr of c is: %p\n", &c);

	a.data = 'a';
	a.next = NULL;

	b.data = 'b';
	b.next = &c;

	c.data = 'c';
	c.next = NULL;

	cursor = &b;

	printf("cursor is at : %c\n", cursor->data);
	printf("cursor addr is : %p\n", cursor);
	printf("cursor->next addr is : %p\n", cursor->next);

	cursor = &a;
	
	printf("cursor is at : %c\n", cursor->data);
	printf("cursor addr is : %p\n", cursor);
	printf("cursor->next addr is : %p\n", cursor->next);

	a.next = &b;

	printf("cursor is at : %c\n", cursor->data);
	printf("cursor addr is : %p\n", cursor);
	printf("cursor->next addr is : %p\n", cursor->next);

	return 0;
}
