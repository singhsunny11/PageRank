#include "random.h"
#include "graph.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

node_t *random_node(graph_t *graph){
  return graph->nodes[randu(graph->count)];
}


node_t *random_out_edge(node_t *node){
  if (node->num_out_edges == 0)
  return NULL;
  else
  return node->outedges[randu(node->num_out_edges)];
}


void simulate_random_surfer(graph_t *graph, int n, double probability) {
    if (graph->count == 0) {
        return;
    }

    int *visit_count = calloc(graph->count, sizeof(int));
    if (!visit_count) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    node_t *current = random_node(graph);

    for (int i=0; i<n; i++) {
        if (current->num_out_edges == 0) {
            current = random_node(graph); 
        } else {
            current = random_out_edge(current);
        }
        int current_index = -1;
        for (int j = 0; j < graph->count; j++) {
            if (graph->nodes[j] == current) {
                current_index = j;
                break;
            }
        }

        if (current_index != -1) {
            visit_count[current_index]++;
        } else {
            fprintf(stderr, "Not found in graph");
            free(visit_count);
            return;
        }
    }

    for (int i=0; i<graph->count; i++) {
        double r_p = (double)visit_count[i]/n;
        printf("%s %.10f\n", graph->nodes[i]->name, r_p);
    }

    free(visit_count);
}