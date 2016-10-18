#include "vector.h"

#include <stdio.h>
#include <stdlib.h>


void
vector_init(Vector_p v) {
    vector_init_with_capacity(v, VECTOR_INIT_CAPACITY);
}

void
vector_init_with_capacity(Vector_p v, int capacity) {
    v->size = 0;
    v->capacity = capacity;
    v->data = malloc(sizeof(int) * v->capacity);
}


void
vector_append(Vector_p v, int value) {
    if (v->size >= v->capacity) {
         v->capacity *= 2;
         v->data = realloc(v->data, sizeof(int) * v->capacity);
    }
    v->data[v->size++] = value;
}


int
vector_get(Vector_p v, int index) {
    if (index < 0 || index >= v->size) {
        printf("Index %d out of bounds for v of size %d\n", index, v->size);
        perror("Index out of bounds");
        return 0;
    }
    return v->data[index];
}


void
vector_set(Vector_p v, int index, int value) {
    if (index < 0 || index >= v->size) {
        perror("Index out of bounds");
        return;
    }
    v->data[index] = value;
}


void
vector_destroy(Vector_p v) {
    free(v->data);
}
