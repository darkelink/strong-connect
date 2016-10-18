#include "graph.h"

#include <ctype.h>
#include <stdlib.h>

void
append_node(Graph_p g, Node node) {
    if (g->size >= g->capacity) {
        // graph is full, expand it
        g->capacity *= 2;
        g->nodes = realloc(g->nodes, sizeof(Node) * g->capacity);
    }
    g->nodes[g->size++] = node;
}

// read the nodes from a file stream until end of line
void
get_nodelist(Node_p node, FILE* fp) {
    node->outList = malloc(sizeof(Vector));
    vector_init(node->outList);

    char ch;
    int current = 0;

    while ((ch = fgetc(fp)) != '\n') {
        if (isdigit(ch)) {
            current = current * 10 + (ch - '0');
        } else if (ch == ' ') {
            vector_append(node->outList, current);
            current = 0;
            // next digit
        } else {
            perror("Encountered unknown character: " + ch);
        }
    }
    // be sure to include last digit
    vector_append(node->outList, current);
    node->degree = node->outList->size;
}

Graph
graph_read(FILE* fp) {
    Graph g;
    g.size = 0;
    g.capacity = GRAPH_INIT_SIZE;
    g.nodes = malloc(sizeof(Node) * g.capacity);

    char ch;
    int current = 0;

    while ((ch = fgetc(fp)) != EOF) {
        Node node;
        // dirty cast to int
        current = ch - '0';

        while ((ch = fgetc(fp)) != ' ') {
            // read base 10 digits one by one until space or newline
            if (isdigit(ch)) {
                current = current * 10 + (ch - '0');
            } else if (ch == '\n') {
                node.degree = 0;
                break;
            } else {
                printf("character %c", ch);
                perror("Encountered unknown character 1");
            }
        }
        node.index = current;
        current = 0;
        if (ch != '\n') {
            get_nodelist(&node, fp);
        }

        append_node(&g, node);

    }
    return g;
}

void
graph_destroy(Graph g) {
    // TODO
}

void
graph_pretty_print(Graph g) {
    printf("Number of nodes: %d\n", g.size);
    for (int i = 0; i < g.size; ++i) {
        for (int j = 0; j < g.nodes[i].degree; ++j) {
            printf("(%d,%d) ",
                    g.nodes[i].index,
                    g.nodes[i].outList->data[j]);
        }
        printf("\n");
    }
}
