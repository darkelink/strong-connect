#include "graph_functions.h"

#include <stdbool.h>
#include <stdlib.h>

// should probably put this somewhere else but it is only used here
static inline int
min(int a, int b) {
    return a < b ? a : b;
}

void
strongconnect(NodeInfo* nodes, int i,
        int* depth, Vector_p stack, StronglyConnected_p output) {

    // use smallest unused depth
    nodes[i].depth   = *depth;
    nodes[i].lowlink = *depth;
    ++(*depth);

    vector_append(stack, i);
    nodes[i].onStack = true;

    // index of node on the other end of an edge
    int next;

    // process all children of current node
    for (int j = 0; j < nodes[i].node->degree; ++j) {
        next = vector_get(nodes[i].node->outList, j);
        if (nodes[next].depth == -1) {
            // node has not been visited yet, so visit it
            strongconnect(nodes, next, depth, stack, output);
            // check for shorter path to node from the root node
            nodes[i].lowlink =
                min(nodes[i].lowlink, nodes[next].lowlink);
        } else if (nodes[next].onStack) {
            // update shortest path from root node
            nodes[i].lowlink =
                min(nodes[i].lowlink, nodes[next].depth);
        }
    }

    // check if we are back at the root
    if (nodes[i].lowlink == nodes[i].depth) {
        // all nodes in the stack are strongly connected to
        // this root node

        // don't process nodes with no children in directed graphs
        if (nodes[i].node->degree > 0) {
            output->areas[++output->size] = malloc(sizeof(Vector));
            vector_init(output->areas[output->size]);
            do {
                next = vector_get(stack, stack->size-1);
                --stack->size;
                nodes[next].onStack = false;
                vector_append(output->areas[output->size], next);
            } while (next != i);
        }
    }
}

StronglyConnected_p
get_strongly_connected(Graph_p g) {
    // don't bother getting the size more than once
    const int graphSize = g->size;

    // lowest available depth (from current root)
    int depth = 0;

    // store all strongly connected nodes from current root node in a stack
    Vector_p stack = malloc(sizeof(Vector));
    vector_init_with_capacity(stack, graphSize);

    // maximum number of strongly connected regions is size of the graph
    // set array length to this to ensure no buffer overflow
    StronglyConnected_p output =
        malloc(sizeof(StronglyConnected) + sizeof(Vector_p) * graphSize);
    output->size = -1;

    // do not make the graph mutable for no reason, store metadata outside it
    NodeInfo nodes[graphSize];
    for (int i = 0; i < graphSize; ++i) {
        nodes[i].node = &g->nodes[i];
        nodes[i].depth = -1;
        nodes[i].onStack = false;
    }

    for (int i = 0; i < graphSize; ++i) {
        if (nodes[i].depth == -1) {
            strongconnect(nodes, i, &depth, stack, output);
        }
    }

    return output;
}

