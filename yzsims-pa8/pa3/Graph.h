// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Name: Yazmyn Sims
// ID: yzsims
// Title: Graph.h
// Description: Header file for Graph ADT (Programming Assignment 3)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include <stdbool.h>
#include <stdio.h>
#include "List.h"

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#define UNDEF -1
#define NIL 0

// //Exported types - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef struct GraphObj* Graph;

/*** Contructors-Destructors ***/
Graph newGraph (int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish (Graph G, int u);

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

/*** Other operations ***/
void printGraph(FILE* out, Graph G);
Graph copyGraph(Graph G);
Graph transpose(Graph G);
#endif
