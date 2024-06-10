#ifndef RANDOM_H
#define RANDOM_H
#include "graph.h"



node_t *random_node(graph_t *graph);

node_t *random_out_edge(node_t *node);

void simulate_random_surfer(graph_t *graph, int steps, double probability);

#endif
