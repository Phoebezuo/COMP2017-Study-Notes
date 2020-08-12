#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node * next;
};

struct node * list_init(int value) {
    struct node * temp = (struct node *)malloc(sizeof(struct node));
    temp->value = value;
    temp->next = NULL;
    return temp;
}

void list_add(struct node* head, int value) {
    struct node *new_node = list_init(value);
    struct node *cur = head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = new_node;
}

void list_delete(struct node **head, struct node* n) {
    struct node *cur = *head;
    if (cur == n) { // the list starts with n
        *head = n->next;
        free(cur);
        return;
    }

    while (cur->next != n) {
        cur = cur->next;
    }
    
    if (cur->next == n) {
        cur->next = n->next;
        free(n);
    } else {
        printf("n is not in this list!\n");
    }
}

struct node* list_next(const struct node *n) {
    return n->next;
}

void list_free(struct node* head) {
    struct node *cur = head;
    while (cur != NULL) {
        struct node *next = list_next(cur);
        free(cur);
        cur = next;
    }
}

int main(){
    struct node *head = list_init(5);
    list_add(head, 10);
    list_add(head, 15);
    list_add(head, 12);
    list_add(head, 20);

    list_delete(&head, head); // 10 15 12 20
    struct node *to_delete = list_next(list_next(head)); // 12
    list_delete(&head, to_delete); // 10 15 20

    struct node *cur = head;
    while (cur != NULL) {
        printf("%d\n", cur->value);
        cur = cur->next;
    }

    list_free(head);
	return 0;
}
