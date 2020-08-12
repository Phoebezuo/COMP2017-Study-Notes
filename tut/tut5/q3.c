#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *prev;
    struct node *next;
};

struct node * list_init(int value) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->value = value;
    new_node->next = new_node;
    new_node->prev = new_node;
    return new_node;
}

void list_add(struct node *head, int value) {
    if (head != NULL) {
        struct node* n = list_init(value);
        struct node* tail = head->prev;
        tail->next = n;
        head->prev = n;
        n->prev = tail;
        n->next = head;
    }
}

void list_delete(struct node **head, struct node *n) {
    if (head == NULL || *head == NULL || n == NULL) { return; }

    if (*head == n) {
        struct node* head_prev = (*head)->prev;
        struct node* current_head = *head;
        *head = (*head)->next;
        (*head)->prev = head_prev;
        free(current_head);
    } else {
        struct node* cur = *head;
        struct node* tail = (*head)->prev;

        while (cur != tail && cur != n) {
            cur = cur->next;
        }

        if (cur == n) {
            struct node* current_prev = cur->prev;
            struct node* current_next = cur->next;
            current_prev->next = current_next;
            current_next->prev = current_prev;
            free(cur);
        }
    }
}

struct node* list_next(const struct node *n) {
    if (n == NULL) { return NULL; }
    return n->next;
}

void list_free(struct node* head) {
    if (head != NULL) {
        struct node *curr = head;
        while (curr != head) {
            struct node *temp = curr->next;
            free(curr);
            curr = temp;
        }
        free(head);
    }
}

void list_traverse(struct node* head) {
    if (head != NULL) {
        struct node* tail = head->prev;
        struct node* cur = head;

        while (cur != tail) {
            printf("%d\n", cur->value);
            cur = cur->next;
        }
        printf("%d\n", cur->value);
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

    list_traverse(head);

    list_free(head);
	return 0;
}
