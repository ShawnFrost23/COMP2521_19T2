// graph.c ... implementation of Graph ADT
// This file was initially taken from labs
// however it has been changed to perform according to requirements.

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"

//========= heading for helper functions go here =========
int found (char *name, char **fileNameArray, int numVer);
int position (char *name, char **fileNameArray, int numVer);

//========= implementaion of helper functions =========
int found (char *name, char **fileNameArray, int numVer) {
  int i = 0;
  while (i < numVer) {
    if (strcmp(fileNameArray[i], name) == 0) {
      return 1;
    }
    i += 1;
  }
  return 0;
}

int position (char *name, char **fileNameArray, int numVer) {
  int returnVal = 0;
  int i = 0;
  while (i < numVer) {
    if (strcmp(name, fileNameArray[i]) == 0) {
      return returnVal;
    }
    returnVal += 1;
    i += 1;
  }
  return 0;
}

//========= implementaion of graph.h functions =========

// check validity of Vertex
int validV(Graph g, Vertex v) {
    return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge(Graph g, Vertex v, Vertex w) {
    assert(g != NULL && validV(g,v) && validV(g,w));
    Edge new = {v,w}; // struct assignment
    return new;
}

// get number of vertices
int getnumV(Graph g) {
    return g->nV;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge(Graph g, Vertex v, Vertex w, int wt) {
    assert(g != NULL && validV(g,v) && validV(g,w));
    if (g->edges[v][w] == 0) {
        g->edges[v][w] = wt;
        g->nE++;
    }
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, Vertex v, Vertex w) {
    assert(g != NULL && validV(g,v) && validV(g,w));
    if (g->edges[v][w] != 0) {
        g->edges[v][w] = 0;
        g->nE--;
    }
}

// create a graph with required data.
Graph newGraph(int nV, char **fileName) {
    assert(nV > 0);
    int v, w;
    Graph new = malloc(sizeof(GraphRep));
    assert(new != 0);
    new->nV = nV;
    new->nE = 0;
    new->edges = malloc(nV*sizeof(int *));
    assert(new->edges != 0);
    for (v = 0; v < nV; v++) {
        new->edges[v] = malloc(nV*sizeof(int));
        assert(new->edges[v] != 0);
        for (w = 0; w < nV; w++)
            new->edges[v][w] = 0;
    }
    int i = 0;
    while (i < nV) {
      char *suffix = ".txt";
      char *openName = malloc(sizeof(strlen(fileName[i]) + strlen(suffix) + 1));
  		strcpy(openName, fileName[i]);
  		strcat(openName, suffix);
      FILE *txtfilePtr = fopen(openName, "r");
      char buffer[3000];
      while (fscanf(txtfilePtr, "%s", buffer) != EOF) {
        if (found(buffer, fileName, nV) == 1) {
          int pos = position(buffer, fileName, nV);
          insertEdge(new, i, pos, 1);
        }
      }
      fclose(txtfilePtr);
      free(openName);
      i += 1;
    }
    int j = 0;
    for(i = 0, j = 0; i < nV; i++, j++){
        if(vLinkw(new,i,j)){
            removeEdge(new, i, j);
        }
    }
    return new;
}

// display graph, using names for vertices
void showGraph(Graph g) {
    assert(g != NULL);
    printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
    int v, w;
    for (v = 0; v < g->nV; v++) {
        for (w = 0; w < g->nV; w++) {
            printf("%d ",g->edges[v][w]);
        }
        printf("\n");
    }
}

// check if vertices v and w are connected
int vLinkw(Graph g, Vertex v, Vertex w) {
    return (g->edges[v][w]);
}

//return number of inLinks for vertex v
double numInLinks(Graph g, Vertex v) {
    int i;
    double inLinks = 0;
    for(i=0; i<g->nV; i++){
        if(g->edges[i][v]){
            inLinks++;
        }
    }
    return inLinks;
}

//return number of outLinks for vertex v
double numOutLinks(Graph g, Vertex v) {
    int i;
    double outLinks = 0;
    for(i=0; i<g->nV; i++){
        if(g->edges[v][i]){
            outLinks++;
        }
    }
    if(outLinks == 0){
        return 0.5;
    } else {
        return outLinks;
    }
}

//return the sum of inLinks for all vertices connected to v
double sumInLinks(Graph g, Vertex v) {
    int i = 0;
    double sum = 0;
    for(i=0; i<g->nV; i++){
        if(g->edges[v][i]){
            sum = sum + numInLinks(g,i);
        }
    }
    return sum;
}

//return the sum of outLinks for all vertices connected to v
double sumOutLinks(Graph g, Vertex v) {
    int i = 0;
    double sum = 0;
    for(i=0; i<g->nV; i++){
        if(g->edges[v][i]){
            sum = sum + numOutLinks(g, i);
        }
    }
    return sum;
}

//free memory associated with graph
void dropGraph(Graph g) {
    assert(g != NULL);
    int i;
    for (i = 0; i < g->nV; i++) {
        free(g->edges[i]);
    }
    free(g->edges);
    free(g);
}
