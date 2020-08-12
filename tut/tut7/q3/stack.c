#include "stack.h"
#include <stdlib.h>

stack* stack_alloc() {
  return (stack*) calloc(sizeof(stack), STACK_INIT_SIZE);
}

void stack_free(stack* s) {
    if(s != NULL) {
        s_node* t = s->top;
        s_node* n = NULL;
        while(t != NULL) {
            n = t->next;
            free(t);
            t = n;
    }
    free(s);
    }
}

s_node* stack_s_node_alloc() {
    return (s_node*) calloc(sizeof(s_node), STACK_NODE_INIT_SIZE);
}

void stack_s_node_free(s_node* n) {
    free(n);
}

void push(stack* s, int v) {
    s_node* n = NULL;
    if(s != NULL) {
        if(s->top == NULL) {
            n = stack_s_node_alloc();
            n->val = v;
            s->top = n;
        } else {
            s_node* s_tmp = s->top;
            n = stack_s_node_alloc();
            n->next = s_tmp;
            n->val = v;
            s->top = n;
        }
    }
}

s_result pop(stack* s) {
    s_result ret = { 0, 0 };
    s_node* t = s->top;
    if(t != NULL) {
        ret.val = t->val;
        s->top = s->top->next;
        stack_s_node_free(t);
    } else {
        ret.failed = 1;
    }
    return ret;
}

s_result peek(stack* s) {
    s_result ret = { 0, 0 };
    s_node* t = s->top;
    if(t != NULL) {
        ret.val = t->val;
    } else {
        ret.failed = 1;
    }
    return ret;
}
