#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
  
graph_t *init_graph(const char *name)
{
graph_t *graph = calloc(1, sizeof(graph_t)); 
if (!graph) {
fprintf (stderr,"No enough memory for graph %s\n", name); 
exit(1);
} 
graph->nodes=NULL;
graph->count=0;
graph->edge_count=0;
graph->name=calloc(strlen(name)+1,sizeof(char));
strcpy(graph->name,name);
return graph;
}

void free_graph(graph_t *graph)
{
    while(graph->count--)
    {
        node_t *node=graph->nodes[graph->count];
        if (node->outedges){
            free(node->outedges);
        }
        if (node->inedges){
            free(node->inedges);
        }
        free(node->name);
        free(node);
    }
    free(graph->name);
    free(graph->nodes);
    free(graph);
    graph=NULL;
}

node_t *get_node_from_graph(graph_t *graph, const char *name){
   for (int i = 0; i < graph->count; i++) {
        if (strcmp(graph->nodes[i]->name, name) == 0) {
            return graph->nodes[i]; // Return existing node
        }
    }
node_t *node=calloc(1,sizeof(node_t));
if (node==NULL){
     fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
}
node->outedges=NULL;
node->inedges=NULL;
node->num_edges=0;
node->num_out_edges = 0;
node->num_in_edges = 0;
node->name=calloc(strlen(name)+1,sizeof(char));
strcpy(node->name,name);
graph->nodes=realloc(graph->nodes,(graph->count+1)*sizeof(node_t *));       ////
graph->nodes[graph->count++]=node;
return node;
}

void add_edge_to_node(node_t *source,node_t *target)
{
source->outedges = realloc(source->outedges , (source ->num_out_edges + 1) * sizeof(node_t *));   ///
if (source->outedges == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE); // Or handle the error appropriately
    }
source->outedges[source->num_out_edges]=target;
source->num_out_edges++;     //num_edges need not be incremented for outedge as already inc in target
target->inedges=realloc(target->inedges,(target->num_in_edges+1)*sizeof(node_t *));
if (target->inedges == NULL) {
        fprintf(stderr,"Memory allocation failed\n");
        exit(EXIT_FAILURE); // Or handle the error appropriately
    }
target->inedges[target->num_in_edges] = source;
target->num_in_edges++;
}

graph_t *read_graph(const char *filename)
{
    FILE* f= fopen(filename,"r");
    if (!f)
    {
    fprintf(stderr,"File could not be opened");
        exit(1);
    }
    char identifier[257];
    char s_name[256];
    char t_name[256];
    int c= fscanf(f,"digraph %255s {\n",identifier);
    graph_t *graph= init_graph(identifier);

   // memset(s_name,0,256);
   // memset(t_name,0,256);

    while(1){
        if((c=fscanf(f,"%255s -> %255s;\n",s_name,t_name))==EOF){
            fprintf(stderr,"Error while reading file\n");
            exit(1);
        }
        if(s_name[0]=='}')break;
        graph->edge_count++;
        if(strlen(t_name)>0)
        {
            t_name[strlen(t_name)-1]= '\0';
        }
        node_t *s_node=get_node_from_graph(graph,s_name);
        node_t *t_node=get_node_from_graph(graph,t_name);
        add_edge_to_node(s_node,t_node);    
    }
    fclose(f);
    return graph;
}  

void print_graph_stats(const char *filename)
{
    graph_t *graph=read_graph(filename);
    if(graph==NULL)
    {
        exit(1);
    }
    printf("%s:\n",graph->name);
    printf("- num nodes: %d\n",graph->count);
    printf("- num edges: %d\n",graph->edge_count);
    int min_indeg= 0;
    int max_indeg= 0;
    int min_outdeg= 0;
    int max_outdeg= 0;
    for (int i=0;i<graph->count;i++){
    node_t *node= graph->nodes[i];
        if(node->num_in_edges<min_indeg)
        {
            min_indeg=node->num_in_edges;
        }
        if (node->num_in_edges>max_indeg)
        {
            max_indeg=node->num_in_edges;
        }
        if (node->num_out_edges<min_outdeg)
        {
            min_outdeg=node->num_out_edges;
        }
        if (node->num_out_edges>max_outdeg)
        {
            max_outdeg=node->num_out_edges;
        }
    }
    printf("- indegree: %d-%d\n",min_indeg,max_indeg);
    printf("- outdegree: %d-%d\n",min_outdeg,max_outdeg);

    free_graph(graph);
    exit(0);

}
