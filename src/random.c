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

void simulate_random_surfer(graph_t *graph, int steps, double probability) {
    if (graph->count==0){
        return;

    }
    int *visit_count = calloc(graph->count, sizeof(int));
    if (!visit_count) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    node_t *current = random_node(graph);
    printf("Starting at: %s\n", current->name);

    for (int i = 0; i < steps; i++) {
        if (current->num_out_edges == 0) {                                         //
            current = random_node(graph);  // Jump to a random node 
        } else {
            current = random_out_edge(current);  // Follow a random outedge
        }

        // Count the visit (excluding the initial state)
        visit_count[current - graph->nodes[0]]++;
    }

    printf("Relative probabilities:\n");
    for (int i = 0; i < graph->count; i++) {
        double relative_probability = (double)visit_count[i] / steps;
        printf("%s %.10f\n", graph->nodes[i]->name, relative_probability);
    }

    free(visit_count);  // Free the allocated memory
}