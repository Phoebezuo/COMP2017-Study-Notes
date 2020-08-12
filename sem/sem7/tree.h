#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

struct bintree_entry {
	void* key;
	void* element;
};

struct bintree_node {
	struct bintree_node* left;
	struct bintree_node* right;
	struct bintree_entry entry;
};

struct bintree {
	struct bintree_node* root;	
	int (*cmp)(void*, void*);
	size_t n_elements;
};


struct bintree* bintree_new(int (*cmp)(void*, void*));

void bintree_put_copy(struct bintree* bin, void* key, size_t ksz, void* value, size_t value_sz);

void bintree_traversal(struct bintree* tree, void (*printer)(void*));
void bintree_destroy(struct bintree* tree);

#endif
