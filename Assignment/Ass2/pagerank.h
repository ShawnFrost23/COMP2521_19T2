//pagerank.h file for pagerank.c
//Made by Arth Patel on 27th July 2019

#include <stdio.h>
#include "graph.h"

// calculate page rank for a given graph with required values.
double *calculatePageRank(Graph g, double damping, double diffPR, int maxIterations);

// sort a given array in descending order according to values of page rank
// and simultaneously upadate the corresponding values of file names and number of out links
// by using bubble sort.
void sortArray(double *pageR, char **fileArray, int outLink[], int arrayLen);

//print the contents required in a text file.
void printToFile(double *pageR, char **fileArray, int outLink[], int arrayLen);
