#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"
#include "rbuf_queue.h"

struct bintree* bintree_new(int (*cmp)(void*, void*)) {
	struct bintree* bin = malloc(sizeof(struct bintree));
	bin->root = NULL;
	bin->cmp = cmp;
	bin->n_elements = 0;
	return bin;
}


static struct bintree_entry bintree_kv_copy(void* key, size_t ksz, 
		void* value, size_t value_sz) {
	//if(key == NULL || value == NULL) { return; }
	//Living on the ed if key is NULL
	struct bintree_entry entry;
	entry.key = malloc(ksz);
	entry.element = malloc(value_sz);
	//key or value could be null, TODO: Fix this!	
	memcpy(entry.key, key, ksz);
	memcpy(entry.element, value, value_sz);
	return entry;
}

static void bintree_put_helper(struct bintree_node* root, void* key, size_t ksz,
		void* value, size_t value_sz, int (*cmp)(void*, void*)) {
	
	int result = cmp(root->entry.key, key);
	if(result == 0) {
		struct bintree_entry ent = bintree_kv_copy(key, ksz, value, value_sz);
		free(root->entry.key);
		free(root->entry.element);
		root->entry = ent;
	} else if(result > 0) {
		if(root->right == NULL) {
			struct bintree_entry ent = bintree_kv_copy(key, ksz, value, value_sz); 
			struct bintree_node* node = malloc(sizeof(struct bintree_node));
			node->left = NULL;
			node->right = NULL;
			node->entry = ent;
			root->right = node;
		} else {
			bintree_put_helper(root->right, key, ksz, value, value_sz, cmp);
		}

	} else {
		if(root->left != NULL) {
			bintree_put_helper(root->left, key, ksz, value, value_sz, cmp);
		} else {	
			struct bintree_entry ent = bintree_kv_copy(key, ksz, value, value_sz); 
			struct bintree_node* node = malloc(sizeof(struct bintree_node));
			node->left = NULL;
			node->right = NULL;
			node->entry = ent;
			root->left = node;
		}
	}

}

void bintree_put_copy(struct bintree* bin, void* key, size_t ksz, 
		void* value, size_t value_sz) {
	
	if(bin == NULL || key == NULL) { return; }

	if(bin->root == NULL) {
		struct bintree_entry entry = bintree_kv_copy(key, ksz, value, value_sz);
		struct bintree_node* node = malloc(sizeof(struct bintree_node));
		node->left = NULL;
		node->right = NULL;
		node->entry = entry;

		bin->root = node;
	} else {
		bintree_put_helper(bin->root, key, ksz, value, value_sz, bin->cmp);
	}
}


static void bintree_traversal_helper(struct bintree_node* node,
		void (*printer)(void*)) {
	 
	if(node != NULL) {
		printer(node->entry.element);

		bintree_traversal_helper(node->left, printer);
		bintree_traversal_helper(node->right, printer);
	}
}

void bintree_traversal(struct bintree* tree, void (*printer)(void*)) {
	bintree_traversal_helper(tree->root, printer);	
}

void bintree_destroy(struct bintree* tree) {
	/*struct rbuf_queue* que = rbuf_new(sizeof(struct bintree_node*));
	struct bintree_node* cur = NULL;
	rbuf_enqueue(que, tree->root);

	while(que->length > 0) {
		cur = rbuf_deque(que);
		
		if(cur->left != NULL) {
			rbuf_enqueue(que, cur->left);
		}

		if(cur->right != NULL) {
			rbuf_enqueue(que, cur->right);
		}	

		fprintf(stdout, "%d\n", *((int*)cur->entry.key));

		free(cur->entry.key);
		free(cur->entry.element);
		free(cur);
	}

	rbuf_delete(que);
	free(tree);*/
  //Fill in the blanks!
}

