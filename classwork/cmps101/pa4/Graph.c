// Graph.c
// Michael Quan
// midquan
// Programing Assignment 4
// Graph ADT constructor with BFS operations


#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define WHITE 0
#define GREY 1
#define BLACK 2

struct GraphObj{
	List* adj;		// array of Lists of ints containing neighbors of vertice number
	int* color;		// array of color values corresponding to vertice number
	int* parent;	// array of parent values corresponding to vertice number
	int* distance; // array of distance values corresponding to vertice number	
	int order;		// # of vertices
	int size;		// # of edges
	int source;		// Vertex last used as source for BFS
};

/*** Constructors-Destructors ***/
//Returns a new Graph of size n 
Graph newGraph(int n){
	Graph G = malloc(sizeof (struct GraphObj));
   G->adj = calloc(n + 1, sizeof(List));
   G->color = calloc(n + 1, sizeof(int));
   G->parent = calloc(n + 1, sizeof(int));
   G->distance = calloc(n + 1, sizeof(int));
   G->order = n;
   G->size = 0;
	G->source = NIL;
	
   for(int i = 1; i <= n; i++) {
      G->adj[i] = newList();
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->distance[i] = INF;
   }
	
   return G;
}

// Frees memory allocated to a Graph
void freeGraph(Graph* pG){
   Graph old = *pG;
   for(int i = 0; i < (old->order + 1); i++) {
      freeList(&(old->adj[i]));
   }
   free(old->adj);
	free(old->color);
   free(old->parent);
   free(old->distance);
 
   free(*pG);
   *pG = NULL;
}

/*** Access functions ***/
// Returns value of order for a given Graph
int getOrder(Graph G){
	if (G == NULL) {
		printf("Cannot call getOrder() from NULL Graph reference. \n");
		exit(1);
	}
	return G->order;
}

// Returns value of size for a given Graph
int getSize(Graph G){
	if ( G == NULL) {
		printf("Cannot call getSize() from NULL Graph reference. \n");
		exit(1);
	}
	return G->size;
}

// Returns the source vertex last used in the function BFS(), or NIL if not called yet
int getSource(Graph G){
	if (G == NULL) {
		printf("Cannot call getSource() from NULL Graph reference. \n");
		exit(1);
	}
	return G->source;
}

// Returns the parent of vertex u last used in the function BFS(), or NIL if not called yet
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
	if (G == NULL) {
		printf("Cannot call getParent() from NULL Graph reference. \n");
		exit(1);
	}
	if(1 <= u || u <= getOrder(G)){
		printf("Cannot call getParent() with an index not contained in the array. \n");
		exit(1);
	}
	return G->parent[u];
}

// Returns the distance of vertex u to the source last used in the function BFS(), or INF if not called yet
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u){
	if (G == NULL) {
		printf("Cannot call getDist() from NULL Graph reference. \n");
		exit(1);
	}
	if(1 <= u || u <= getOrder(G)){
		printf("Cannot call getDist() with an index not contained in the array. \n");
		exit(1);
	}
	return G->distance[u];
}


// Returns the path from vertex u to the source used in the function BFS(), or NIL if not called yet
// Appends the List L with the vertices of the shortest path
// Pre: 1 <= u <= getOrder(G)
// Pre: getSource(G) != NIL
void getPath(List L, Graph G, int u){
	if (L == NULL) {
		printf("Cannot call getPath() from NULL List reference. \n");
		exit(1);
	}
	if (G == NULL) {
		printf("Cannot call getPath() from NULL Graph reference. \n");
		exit(1);
	}
	if(1 <= u || u <= getOrder(G)){
		printf("Cannot call getPath() with an index not contained in the array. \n");
		exit(1);
	}
	if(getSource(G) == NIL){
		printf("Cannot call getPath() without a source from a given vertex  \n");
		exit(1);
	}
	if(u == G->source) prepend(L, G->source);
	else if(G->parent[u] == NIL) append(L, NIL);
	else{
		prepend(L, u);
		getPath(L, G, G->parent[u]);
	}
}

// Deletes all edges of G, making it back to its original NULL state
/*** Manipulation procedures ***/
void makeNull(Graph G){
	if (G == NULL) {
		printf("Cannot call makeNull() from NULL Graph reference. \n");
		exit(1);
	}
	for(int i = 1; i <= G->order; i++) clear(G->adj[i]);
}
// Insert an edge joining u to adjacency List of v and vice versa
// Pre: 1 <= u <= getOrder(G); 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v){
	if (G == NULL) {
		printf("Cannot call addEdge() from NULL Graph reference. \n");
		exit(1);
	}
	if(1 <= u || u <= getOrder(G) || 1 <= v || v <= getOrder(G)){
		printf("Cannot call addEdge() with an index not contained in the array. \n");
		exit(1);
	}
	addArc(G, u, v);
	addArc(G, v, u);
	G->size--;
}


// Insert a directed edge joining u to v to the adjancency List of u
// Pre: 1 <= u <= getOrder(G); 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v){
	if (G == NULL) {
		printf("Cannot call addArc() from NULL Graph reference. \n");
		exit(1);
	}
	if(1 <= u || u <= getOrder(G) || 1 <= v || v <= getOrder(G)){
		printf("Cannot call addArc() with an index not contained in the array. \n");
		exit(1);
	}
	List L = G->adj[u];
	//insertAfterBack(G->adj[u], v);
	while(index(L) > -1 && v > get(L)) {
		moveNext(L);
   }
	
   if(index(L) == -1) append(L, v);
   else insertBefore(L, v);
	
	G->size++;
}

// Runs BFS on the Graph G with source s
// Fills out the color, distance, and parent fields of G aswell
// Pre: 1 <= s <= getOrder(G);
void BFS(Graph G, int s){
	if (G == NULL) {
		printf("Cannot call BFS() from NULL Graph reference. \n");
		exit(1);
	}
	if(1 <= s || s <= getOrder(G)){
		printf("Cannot call BFS() with an index not contained in the array. \n");
		exit(1);
	}
	
	for(int i = 1; i <= getOrder(G); i++){
		G->color[i] = 	WHITE;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->color[s] = GREY;
	G->distance[s] = 0;
	G->source = s;
	List Q = newList();
	prepend(Q,s);
	while (length(Q) > 0){
		int temp = back(Q);
		deleteBack(Q);
		List adj = G->adj[temp];
		moveFront(adj);
		while(index(adj) > -1){
			int z = get(adj);
			if(G->color[z] == WHITE){
				G->color[z] = GREY;
				G->parent[z] = temp;
				G->distance[z] = G->distance[temp] + 1;
				prepend(Q, z);
			}
			moveNext(adj);
		}
	}
	freeList(&Q);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	if (out == NULL || G == NULL) {
		printf("Cannot call printGraph() from NULL Graph reference. \n");
		exit(1);
	}
	for(int i = 1; i <= getOrder(G); i++){
		fprintf(out, "%d ", i);
		printList(out, G->adj[i]);
		fprintf(out, "\n");
	}
}