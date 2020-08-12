#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int main(void) {

	struct node *head = malloc(sizeof(struct node));
    head->data = (int*)1;

    struct node *a = malloc(sizeof(struct node));
    a->data = (int*)2;

    struct node *b = malloc(sizeof(struct node));
    b->data = (int*)3;

    struct node *c = malloc(sizeof(struct node));
    c->data = (int*)4;

    struct node *d = malloc(sizeof(struct node));
    d->data = (int*)5;

    list_init(head);
    list_append(head, a);
    list_append(head, b);
    list_append(head, c);
    list_append(head, d);
    // list: 1 2 3 4 5

    list_delete(head); // 2 3 4 5

    struct node *e = malloc(sizeof(struct node));
    e->data = (int*)10;
    list_push(head, e); // 10 2 3 4 5

	// traverse the list
	node* tail = head->prev;
	node* cur = head;
	while (cur != tail) {
		printf("%d\n", (int)cur->data);
		cur = cur->next;
	}
	printf("%d\n", (int)cur->data);

    printf("the list is empty? %d\n", list_empty(head));
	return 0;
}
