//searchPagerank.h file for searchPagerank.c
//Made by Arth Patel on 1st August 2019

#include <stdio.h>

// function to get page ranks for an array containing particular URLs.
double *getPageRanks(char **array, int length);

//sort URL array according to decreasing order of page ranks by buble sort.
void sortArray(char **urlArray, double *pageRankArray, int length);

//print the array to terminal.
void printToTerminal(char **array, int length);

//remove full stops, commas at the end of words.
void normalise(char *word);
