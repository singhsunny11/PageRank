#ifndef MARKOV_H
#define MARKOV_H
#include "graph.h"

int links(node_t *source,node_t *target);
void simulate_markov(graph_t *graph, int n,double p);

#endif
