//implementation of pagerank.h
//Made by Arth Patel on 27th July 2019

#include "pagerank.h"
#include "graph.h"

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <ctype.h>
#include <math.h>

//========= heading for helper functions go here =========
void swapPageRank(double *pageR, int i, int j);
void swapFileName(char **fileArray, int i, int j);
void swapOutGoingLink(int outLink[], int i, int j);
void dropArray(char **array, int length);

//========= implementaion of helper functions =========
void swapPageRank(double *pageR, int i, int j) {
  double tempPageRank;
  tempPageRank = pageR[j];
  pageR[j] = pageR[i];
  pageR[i] = tempPageRank;
}

void swapFileName(char **fileArray, int i, int j) {
  char *tempFileName;
  tempFileName = fileArray[j];
  fileArray[j] = fileArray[i];
  fileArray[i] = tempFileName;

}

void swapOutGoingLink(int outLink[], int i, int j) {
  int tempOutLink;
  tempOutLink = outLink[j];
  outLink[j] = outLink[i];
  outLink[i] = tempOutLink;
}

void dropArray(char **array, int length) {
    int i = 0;
    while (i < length) {
        free(array[i]);
        i += 1;
    }
    free(array);
}

//========= Main function =========
int main(int argc, char const *argv[]) {

  if (argc != 4) {
    printf("Supply 3 arguments: damping factor, difference in PageRank sum, maximum iterations\n");
    exit(1);
  }

  //get the variables from command line.
  double damping = atof(argv[1]);
  double diffPRsum = atof(argv[2]);
  int maxIt = atoi(argv[3]);

  //store the name of files from collection to our file name Array.
  char **fileArray = NULL;
  int totalfiles = 0;
  FILE *filePtr = fopen("collection.txt", "r");
  char buffer[100];
  while (fscanf(filePtr, "%s", buffer) != EOF) {
    fileArray = realloc(fileArray, (totalfiles + 1) * (sizeof(char*)));
    fileArray[totalfiles] = malloc(strlen(buffer) + 1);
    strcpy(fileArray[totalfiles++], buffer);
  }
  fclose(filePtr);

  //make graph with the file names.
  Graph newG = newGraph(totalfiles, fileArray);

  //initialise array for of outgoing urls for each url.
  int outGoingLinks[totalfiles];

  //pointer to page rank array.
  double *pageRank = malloc(sizeof(double)*getnumV(newG));

  //calculate page rank for the graph vertices.
  pageRank = calculatePageRank(newG, damping, diffPRsum, maxIt);

  //get the number of outLinks for each URL and store in outgoing array.
  int i = 0;
  while (i < totalfiles) {
      outGoingLinks[i] = numOutLinks(newG, i);
      i += 1;
  }

  //sort the pageRank array and simultaneously update fileArray and outgoing arrays as well.
  sortArray(pageRank, fileArray, outGoingLinks, totalfiles);

  //print the contents to a file.
  printToFile(pageRank, fileArray, outGoingLinks, totalfiles);

  //Free memory used by the graph
  dropGraph(newG);

  //Free memory used by the file name array
  dropArray(fileArray, totalfiles);

  //Free memory used by page rank array.
  free(pageRank);

  return 0;
}

//========= implementaion of functions in pageRank.h =========
double *calculatePageRank(Graph g, double damping, double diffPR, int maxIterations) {

  int nV = getnumV(g);
  double nVfloat = (double)nV;
  double *pageR = malloc(sizeof(double)*nV);
  double oldPR[nV];

  // set every URLs page rank intially zero.
  int h = 0;
  while (h < nV) {
    pageR[h] = 1/nVfloat;
    h += 1;
  }

  int i = 0;
  int j = 0;
  int k = 0;
  int itera = 0;
  double diff = diffPR;
  double wIn = 0;
  double wOut = 0;
  double summation = 0;
  double diffSum = 0;

  while (itera < maxIterations && diff >= diffPR) {
    for(i = 0; i < nV; i += 1) {
      oldPR[i] = pageR[i];
    }
    i = 0;
    while (i < nV) {
      summation = 0;
      j = 0;
      while (j < nV) {
        if (vLinkw(g, j, i)) {
          wIn = (numInLinks(g, i)/sumInLinks(g, j));
          wOut = (numOutLinks(g, i)/ sumOutLinks(g, j));
          summation += (oldPR[j] * wIn * wOut);
        }
        j += 1;
      }
      pageR[i] = ((1-damping)/nVfloat) + (damping * summation);
      i += 1;
    }
    diffSum = 0;
    k = 0;
    while (k < nV) {
      diffSum += fabs(pageR[k]- oldPR[k]);
      k += 1;
    }
    diff = diffSum;
    itera += 1;
  }

  return pageR;
}

void sortArray(double *pageR, char **fileArray, int outLink[], int arrayLen) {
  int i = 0, j = 0;
  while (i < arrayLen) {
    j = 0;
    while (j < arrayLen) {
      if (pageR[j] < pageR[i]) {
        swapPageRank(pageR, i, j);

        swapFileName(fileArray, i, j);

        swapOutGoingLink(outLink, i, j);
      }
      j += 1;;
    }
    i += 1;
  }
}

void printToFile(double *pageR, char **fileArray, int outLink[], int arrayLen) {
  int i = 0;
  FILE *writePtr = fopen("pagerankList.txt", "w");

  while (i < arrayLen) {
    fprintf(writePtr, "%s, %d, %.7f\n", fileArray[i], outLink[i], pageR[i]);
    i += 1;
  }
  fclose(writePtr);
}
