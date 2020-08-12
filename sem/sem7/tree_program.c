#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cmocka.h>
#include "tree.h"

int icompare(void* a, void* b) {
	int* x = (int*) a;
	int* y = (int*) b;

	return a - b;
}

void test_init(void** state) {

	struct bintree* t = bintree_new(icompare);
	assert_non_null(t);

	free(t);

}


void print_obj(void* obj) {
	char* i = (char*) obj;
	fprintf(stderr, "%s\n", i);
}

void test_tree_place_afew(void** state) {
	struct bintree* t = bintree_new(icompare);

	int numbers[] = { 10, 5, 15, 2, 7, 14, 19, 8 };
	char strs[8][8] = {
			"A", "B", "C", "D", "E", "F", "G", "Jeff"
	};

	for(int i = 0; i < 8; i++) {
		bintree_put_copy(t, numbers+i, sizeof(int), strs+i, 8); 
	}
	bintree_traversal(t, print_obj);
	bintree_destroy(t);
}


int main() {
	
	struct CMUnitTest tests[] = {
		cmocka_unit_test(test_init),
		cmocka_unit_test(test_tree_place_afew)
	};



	cmocka_run_group_tests(tests, NULL, NULL);

	test_tree_place_afew(NULL);

	return 0;
}
