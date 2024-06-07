#ifndef GRAPH_H
#define GRAPH_H

typedef struct node{
    struct node **outedges;
    struct node **inedges;
    int num_edges;
    int num_out_edges;
    int num_in_edges;
    char* name;
}node_t;

typedef struct graph{
    node_t **nodes;
    int count;
    int edge_count;
    char *name;
}graph_t;

void print_graph_stats(const char *filename);

graph_t *read_graph(const char *filename);

graph_t *init_graph(const char *);

void free_graph(graph_t *);

node_t *get_node_from_graph(graph_t *, const char *);

void add_edge_to_node(node_t *, node_t *);

#endif