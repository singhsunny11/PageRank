#include "random.h"
#include "graph.h"
#include "utils.h"
#include "random.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>



int links(node_t *source,node_t *target){
    int num = 0;
    for (int i = 0; i < source->num_out_edges; i++) {
        if (source->outedges[i] == target) {
            num++;
        }
    }
    return num;
}

void simulate_markov(graph_t *graph,int n,double p){
    int states=graph->count;
    double *initial_vector=calloc(states,sizeof(double));
    double *t_matrix=calloc(states*states,sizeof(double));

    for (int i=0;i<states;i++){
        initial_vector[i]=1.0/states;     
    }
    for(int i=0;i<states;i++){
        for (int j=0;j<states;j++){
            if(graph->nodes[i]->num_out_edges==0){
                t_matrix[i*states+j]=1.0/states;
            }
            else{
                int num_links = links(graph->nodes[i], graph->nodes[j]);
                t_matrix[i*states+j]=(p/states)+(((1-p)*num_links)/graph->nodes[i]->num_out_edges);
            }
        }
    }

    for(int i=0;i<n;i++){
        double *new_vector=calloc(states,sizeof(double));

        for(int j=0;j<states;j++){
            double sum=0;
            for(int k=0;k<states;k++){
                sum+=initial_vector[k] * t_matrix[k*states+j];
            }
            new_vector[j]=sum;
        }
        for(int i=0;i<states;i++){
            initial_vector[i]=new_vector[i];
        }
        memcpy(initial_vector, new_vector, states * sizeof(double));
        free(new_vector);
    }
    for(int i=0;i<states;i++){
        printf("%s %.10f\n",graph->nodes[i]->name, initial_vector[i]);
    }
    free(initial_vector);
    free(t_matrix);
    exit(0);
}