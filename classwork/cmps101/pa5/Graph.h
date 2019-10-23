// Graph.h
// Michael Quan
// midquan
// Programing Assignment 5
// Header file for Graph

//-----------------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------


#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_


#include <stdio.h>
#include "List.h"

#define NIL -2
#define UNDEF -3


typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);

void freeGraph(Graph* pG); 

/*** Access functions ***/
int getOrder(Graph G);

int getSize(Graph G);

int getParent(Graph G, int u); /* Pre: 1 <= u <= getOrder(G) */

int getDiscover(Graph G, int u); /* Pre: 1 <= u <= getOrder(G) */

int getFinish(Graph G, int u); /* Pre: 1 <= u <= getOrder(G) */

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void DFS(Graph G, List S);

/*** Other operations ***/
Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out, Graph G);

#endif