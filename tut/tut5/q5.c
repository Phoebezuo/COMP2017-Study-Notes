#include <stdio.h>
#include <stdlib.h>

#define DYN_ARRAY_DEF_CAPACITY (8)

struct dyn_array {
    int capacity;
    int size;
    int *data;
};

static void dyn_array_resize(struct dyn_array* array) {
    array->capacity *= 2;
    array->data = realloc(array, sizeof(*(array->data) * array->capacity));
}

struct dyn_array* dyn_array_init(){
    struct dyn_array *array = malloc(sizeof(struct dyn_array));
    array->capacity = DYN_ARRAY_DEF_CAPACITY;
    array->size = 0;
    array->data = malloc(sizeof(*(array->data) * array->capacity)); // size of data type times capacity
    return array;
}

void dyn_array_add(struct dyn_array* array, int value) {
    if (array != NULL) {
        if (array->size >= array->capacity) {
            int* temp = realloc(array->data, array->capacity*2);
            if (temp != NULL) {
                array->data = temp;
                array->capacity = array->capacity * 2;
            } else {
                fprintf(stderr, "Cannot resize array");
                return;
            }
        }
        array->data[array->size++] = value;
    }
}

void dyn_array_delete(struct dyn_array* array, int index) {
    if (array != NULL) {
        if (index >= 0 && index < array->size) {
            // move 4*(size-index) bytes from data+index+1 to index
            memmove(array->data + index,
                    array->data + index + 1,
                    sizeof(int) * (array->size -index));
        }
    }
}

int* dyn_array_get(struct dyn_array* array, int index) {
    if (array != NULL) {
        if (index >= 0 && index < array->size) {
            return array->data + index; // aka array[index]
        }
    }
    return NULL;
}

void dyn_array_free(struct dyn_array* array) {
    free(array->data);
    free(array);
}

int main() {
    struct dyn_array* array = dyn_array_init();

    for (int i = 1; i < 100; i++) {
        dyn_array_add(array, i);
    }

    dyn_array_delete(array, 97); // 98 disappear

    for (int i = 0; i < array->size; i++) {
        printf("%d\n", *dyn_array_get(array, i));
    }

    dyn_array_free(array);

    return 0;
}
