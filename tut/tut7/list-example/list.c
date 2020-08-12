#include "list.h"

// Initializes an empty circular linked list.
void list_init(node* head) {
	head->next = head;
	head->prev = head;
}

// Inserts given node before the head.
void list_push(node* head, node* n) {
	n->prev = head;
	n->next = head->next;

	n->next->prev = n;
	n->prev->next = n;
}

// Inserts given node after the head.
void list_append(node* head, node* n) {
	n->prev = head->prev;
	n->next = head;

	n->prev->next = n;
	n->next->prev = n;
}

// Removes the given node from the list.
void list_delete(node* n) {
	n->prev->next = n->next;
	n->next->prev = n->prev;
}

// Returns whether the list is empty.
int list_empty(node* head) {
	return head->prev == head;
}
