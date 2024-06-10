#include "argparser3.h"
#include "graph.h"
#include "random.h"
#include "markov.h"
#include <err.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



double p =0.1;
char *dot_file_name;
int random_surfer_steps=0;
int markov_steps=0;

void parse_arguments(int const argc, char **const argv){
   int option;
   int flag_s=0;
   int flag_hrm=0;
   if (argc<2) {
    fprintf(stderr, "Invalid command line arguments\n");
    exit(EXIT_FAILURE);
}
    while ((option = getopt(argc, argv, "hr:m:sp:")) != -1)
    {
        switch (option)
        {
        case 'h':{
            char *str= argv[0];
            printf("Usage: %s [OPTIONS] ... [FILENAME] \n", str);
            printf("Perform pagerank computations for a given file in the DOT format\n");
            printf("\n");
            printf("-h Print a brief overview of the available command line parameters\n");
            printf("-r N Simulate N steps of the random surfer and output the result\n");
            printf("-m N Simulate N steps of the Markov chain and output the result\n");
            printf("-s Compute and print the statistics of the graph\n");
            printf("-p P Set the parameter p to P%%. (Default: P = 10)\n");
            flag_hrm=1;
            exit(EXIT_SUCCESS);
        }
        case 'r': {
            char *end;
                random_surfer_steps = strtoul(optarg, &end, 0);
                if (end == optarg || *end != '\0') {
                    errx(EXIT_FAILURE, "invalid N '%s'", optarg);
                }
                flag_hrm=1;
               break;
        }
        case 'm':{
            char *end;
            markov_steps= strtoul(optarg, &end, 0);
            if(end==optarg || *end != '\0'){
                errx(EXIT_FAILURE, "invalid N '%s'", optarg);
            } 
            flag_hrm=1;
            break;
        }
        case 'p': {
                char *end;
                p = strtod(optarg, &end)/100.0;
                if (end == optarg || *end != '\0' || p <= 0 || p > 1) {
                    errx(EXIT_FAILURE, "invalid P '%s'", optarg);
                }
                break;
            }
       case 's':{
        flag_s=1;
            break;
        }
       default:{
        errx(EXIT_FAILURE, "Unknown option: %c", option);
        break;
        } 
    }
    }
    if (optind < argc) {
        dot_file_name = argv[optind];
    } else {
        fprintf(stderr, "No input file specified.\n");
        exit(EXIT_FAILURE);
    }
    if(flag_hrm==0 && flag_s==0){
        fprintf(stderr,"atleast one option must be provided");
        exit(EXIT_FAILURE);
    }
    if (flag_s)
    print_graph_stats(dot_file_name);
    if (random_surfer_steps){
    graph_t *graph=read_graph(dot_file_name);
    simulate_random_surfer(graph,random_surfer_steps,p);
    free_graph(graph);
    }
    if(markov_steps){
    graph_t *graph=read_graph(dot_file_name);
    simulate_markov(graph,markov_steps,p);
    free_graph(graph);   
    }
    exit(EXIT_SUCCESS);
}


