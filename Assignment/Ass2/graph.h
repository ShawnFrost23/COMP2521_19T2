// Graph.h ... interface to Graph ADT
// This file was initially taken from labs
// however it has been changed to perform according to requirements.

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

// graph representation (adjacency matrix)
typedef struct GraphRep {
    int    nV;    // #vertices
    int    nE;    // #edges
    int  **edges; // matrix of weights (0 == no edge)
} GraphRep;

// graph representation is hidden
typedef struct GraphRep *Graph;

// vertices denoted by integers 0..N-1
typedef int Vertex;
int validV(Graph,Vertex); //validity check

// edges are pairs of vertices (end-points)
typedef struct { Vertex v; Vertex w; } Edge;
Edge mkEdge(Graph g, Vertex v, Vertex w);
void insertEdge(Graph, Vertex, Vertex, int);
void removeEdge(Graph, Vertex, Vertex);

// operations on graphs
Graph newGraph(int nV, char **fileName);
void showGraph(Graph);
int getnumV(Graph g);
int vLinkw(Graph g, Vertex v, Vertex w);
double numInLinks(Graph g, Vertex v);
double numOutLinks(Graph g, Vertex v);
double sumInLinks(Graph g, Vertex v);
double sumOutLinks(Graph g, Vertex v);
void dropGraph(Graph g);

#endif
