#pragma once

#include "graph.h"
#include "vector.h"

// store metadata outside the graph so it stays immutable
typedef struct {
    Node_p node;
    int depth;
    int lowlink;
    int onStack;
} NodeInfo, *NodeInfo_p;

// 2d array of strongly connected node indexes
typedef struct {
    int size;
    Vector_p areas[];
} StronglyConnected, *StronglyConnected_p;

// get all strongly connected areas for a graph
StronglyConnected_p get_strongly_connected(Graph_p g);
