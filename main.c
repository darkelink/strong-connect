#include "graph.h"
#include "graph_functions.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void
print_usage() {
    printf("usage: ex1 [-p] graph\n  -p: print graph structure\n  graph: file containing the graph data\n");
}

int
main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage();
        exit(EXIT_FAILURE);
    }

    int pflag = false;

    int c;
    while ((c = getopt (argc, argv, "ph:")) != -1) {
        switch (c) {
            case 'p':
                pflag = true;
                break;
            case 'h':
                print_usage();
                exit(EXIT_SUCCESS);
                break;
            default:
                print_usage();
                exit(EXIT_FAILURE);
        }
    }

    // assume file name is always last argument
    FILE *fp = fopen(argv[argc-1], "r");
    if (fp == NULL) {
        perror("Error when opening file");
        exit(EXIT_FAILURE);
    }

    Graph g = graph_read(fp);
    fclose(fp);

    if (pflag) {
        graph_pretty_print(g);
    }

    StronglyConnected_p areas = get_strongly_connected(&g);

    for (int i = 0; i <= areas->size; ++i) {
        for (int j = 0; j < areas->areas[i]->size; ++j) {
            printf("%d ", vector_get(areas->areas[i], j));
        }
        printf("\n");
    }

    graph_destroy(g);
    return EXIT_SUCCESS;
}
