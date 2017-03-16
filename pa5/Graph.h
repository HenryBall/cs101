// Graph.h
// Henry Ball
// hfball
// pa4
// Header file for Graph ADT

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include "List.h"

#define UNDEF -1
#define NIL 0

// Exported type ---------------------------------------------------------------
typedef struct GraphObj* Graph;

// Constructors-Destructors ----------------------------------------------------
Graph newGraph(int n);
void freeGraph(Graph* pG);

// Access functions ------------------------------------------------------------
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

// Manipulation procedures ----------------------------------------------------
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

// Other ---------------------------------------------------------------------
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE *out, Graph G);


#endif




