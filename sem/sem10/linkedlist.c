#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>


struct node {
	struct node* next;
	int value;
};


struct linkedlist {
	pthread_mutex_t lock;
	struct node* head;	
};

void linkedlist_add(struct linkedlist* list, int value) {
	
	if(list != NULL) {
		if(list->head == NULL) {
			
			pthread_mutex_lock(&list->lock);		
			list->head = malloc(sizeof(struct node));
			list->head->value = value;
			list->head->next = NULL;
		} else {

			struct node* n = malloc(sizeof(struct node));
			n->value = value;
			n->next = NULL;
			
			struct node* cursor = list->head;
			while(cursor->next != NULL) {
				cursor = cursor->next;
			}
			
			pthread_mutex_lock(&list->lock);		
			if(cursor->next == NULL) {
				cursor->next = n;
			} else {

				pthread_mutex_unlock(&(list->lock));
				free(n);
				linkedlist_add(list, value);
			}
		}
	}

	pthread_mutex_unlock(&(list->lock));
}

void linkedlist_traverse(struct linkedlist* list) {
	int count = 0;
	struct node* cursor = list->head;
	while(cursor != NULL) {
		printf("%d\n", cursor->value);
		cursor = cursor->next;
		count++;
	}
	printf("COUNT: %d\n", count); 
}

struct thread_arg {
	struct linkedlist* list;
	int start;
	int n;
};

void* thread_add(void* arg) {
	struct thread_arg* a = (struct thread_arg*) arg;
		
	for(int i = 0; i < a->n; i++) {
		linkedlist_add(a->list, a->start++);
	}
	free(a);
	return NULL;
}

void linkedlist_destroy(struct linkedlist* list) {
	struct node* n = list->head;
	struct node* temp = NULL;
	while(n != NULL) {
		temp = n->next;
		free(n);
		n = temp;
	}
	free(n);
	free(list);
}

int main() {
	
	struct linkedlist* list = malloc(sizeof(struct linkedlist));
	list->head = NULL;
	pthread_mutex_init(&(list->lock), NULL);	
	pthread_t threads[3];

	int n = 10000;
	for(int i = 0; i < 3; i++) {
		struct thread_arg* a = malloc(sizeof(struct thread_arg));
		a->list = list;
		a->start = i*n;
		a->n = n;
		pthread_create(threads+i, NULL, &thread_add, a); 
	}

	for(int i = 0; i < 3; i++) {
		pthread_join(threads[i], NULL);
	}
	linkedlist_traverse(list);
	linkedlist_destroy(list);
}
