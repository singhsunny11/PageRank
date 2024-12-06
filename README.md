# PageRank Algorithm

## Description
An implementation of the PageRank algorithm used to rank web pages based on link structure and relevance. This project demonstrates how Google's PageRank algorithm works by calculating the importance of web pages in a network.

## Overview
This project aims to calculate the PageRank of nodes in a directed graph, representing websites interconnected by hyperlinks. The implementation employs two distinct approaches to determine the PageRank:
1. Random Surfer Model: This method approximates PageRank by simulating the behavior of a random user navigating through the network of websites.
2. Markov Chain Model: This approach leverages mathematical principles to compute PageRank with greater accuracy.

## Execution
```bash
./pagerank [OPTIONS]... [FILENAME]
```

### OPTIONS
- -h : Print a brief overview of the available command line parameters.
- -r N : Simulate N steps of the random surfer and output the result.
- -m N : Simulate N steps of the Markov chain and output the result.
- -s : Compute and print the statistics of the graph.
- -p P : Set the probability parameter p for the random surfer model (default is 10%).

### Examples
To display all the available command line parameters:
```bash 
./pagerank -h
```
To simulate the random surfer behavior for 100 steps using the graph described in graph.dot.
```bash
./pagerank -r 500 graph.dot
```
To simulate 100 steps of the Markov chain with probability(=15):
```bash
 ./ pagerank -m 100 -p 15 prgraph.dot
```
