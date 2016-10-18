#pragma once

#define VECTOR_INIT_CAPACITY 4

typedef struct {
    int size;
    int capacity;
    int* data;
} Vector, *Vector_p;

// initialise a vector of default capacity
void vector_init(Vector* v);
// initialise a vector of given capacity
void vector_init_with_capacity(Vector* v, int capacity);
// append an int to a vector, increasing it's capacity to fit
void vector_append(Vector* v, int value);
// get int at index
int  vector_get(Vector* v, int index);
// set int at index
void vector_set(Vector* v, int index, int value);
// safely free memory of a vector
void vector_destroy(Vector* v);
