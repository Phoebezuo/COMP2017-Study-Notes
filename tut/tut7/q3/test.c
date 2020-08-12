#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "stack.h"

stack* s;
s_result res;
size_t size;

struct testcase {
    char* name;
    int (*fn)();
};

int test_initialised() {
    s = stack_alloc();
    return true;
}

int test_add() {
    push(s, 5);
    return true;
}

int test_pop() {
    res = pop(s);
    if (!res.failed) {
        return true;
    } else {
        return false;
    }
}

int test_retrieve() {
    size = s->size;
    return true;
}

int test_deallocated() {
    stack_free(s);
    return true;
}

int test_null() {
    s = stack_alloc();
    push(s, (int) NULL);
    return true;
}

struct testcase tests[] = {
    {.name = "test_initialised", .fn = test_initialised},
    {.name = "test_add", .fn = test_add},
    {.name = "test_pop", .fn = test_pop},
    {.name = "test_deallocated", .fn = test_deallocated},
    {.name = "test_retrieve", .fn = test_retrieve},
    {.name = "test_null", .fn = test_null},
};

int main(int argc, char** argv) {
    if (argc >= 2) {
        size_t n_tests = sizeof(tests)/sizeof(struct testcase);

        // if the input is all
        if (strcmp("all", argv[1]) == 0) {
            for (int i = 0; i < n_tests; i++) {

                // if fn is exited in struct testcase
                if (tests[i].fn() != false) {
                    fprintf(stdout, "%s Passed\n", tests[i].name);
                } else {
                    fprintf(stdout, "%s Failed\n", tests[i].name);
                }
            }
        } else {
            for (int i = 0; i < n_tests; i++) {

                if (strcmp(tests[i].name, argv[1]) == 0) {

                    // if fn is exited in struct testcase
                    if (tests[i].fn() != false) {
                        fprintf(stdout, "%s Passed\n", tests[i].name);
                    } else {
                        fprintf(stdout, "%s Failed\n", tests[i].name);
                    }
                    break;
                }
            }
        }
    }
}
