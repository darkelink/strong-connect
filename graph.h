#pragma once

#include "vector.h"

#include <stdio.h>

#define GRAPH_INIT_SIZE 8

typedef struct {
    int index;
    int degree;
    Vector_p outList;
} Node, *Node_p;

typedef struct {
    int size;
    int capacity;
    Node_p nodes;
} Graph, *Graph_p;

// read graph from file
Graph graph_read(FILE* fp);
// safely clean graph memory
void graph_destroy(Graph g);
// print a representation of the graph
void graph_pretty_print(Graph g);
