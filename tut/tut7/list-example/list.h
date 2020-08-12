#ifndef LIST_H
#define LIST_H

typedef struct node node;
struct node {
	void* data;
	node* next;
	node* prev;
};

// Initializes an empty circular linked list.
void list_init(node* head);

// Inserts given node before the head.
void list_push(node* head, node* n);

// Inserts given node after the head.
void list_append(node* head, node* n);

// Removes the given node from the list.
void list_delete(node* n);

// Returns whether the list is empty.
int list_empty(node* head);

#endif
