#ifndef ARGPARSER3_H
#define ARGPARSER3_H

#include <stdbool.h>
#include <stdint.h>

void parse_arguments(int argc, char **argv);

extern double n;
extern double p;
extern char *dot_file_name;
extern int random_surfer_steps;
extern int markov_steps;

#endif

