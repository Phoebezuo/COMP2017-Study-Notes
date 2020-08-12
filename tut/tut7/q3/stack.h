#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#define STACK_INIT_SIZE (1)
#define STACK_NODE_INIT_SIZE (1)

typedef struct s_node s_node;
typedef struct stack stack;
typedef struct s_result s_result;

struct s_node {
    int val;
    s_node* next;
};

struct stack {
    s_node* top;
    size_t size;
};

struct s_result {
    int val;
    int failed;
};

stack* stack_alloc();
s_node* stack_s_node_alloc();

void push(stack* s, int v);
s_result pop(stack* s);
s_result peek(stack* s);

void stack_free(stack* s);
void stack_s_node_free(s_node* n);

#endif
