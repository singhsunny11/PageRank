#include "argparser3.h"
#include "graph.h"
#include <err.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


double p =10;
char *dot_file_name;

void parse_arguments(int const argc, char **const argv){
   int option;
   int flag_s=0;
    while ((option = getopt(argc, argv, "hs")) != -1)
    {
        switch (option)
        {
       case -1:
        {
            if (argc-optind!=1)
            {
                return;
            }
            dot_file_name=argv[optind];
            break;
        }
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
            break;
        }
       case 's':{

        if (optind < argc) {
                    dot_file_name = argv[optind];
                    print_graph_stats(dot_file_name);
                }
            
        //flag_s=1;
            break;
        }
        } 
    }

}
