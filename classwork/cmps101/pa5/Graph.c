// Graph.c
// Michael Quan
// midquan
// Programing Assignment 5
// Graph ADT constructor with DFS operations


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
	int* discover; // array of discover values corresponding to vertice number	
	int* finish; 	// array of finish values corresponding to vertice number	
	int order;		// # of vertices
	int size;		// # of edges
};

/*** Constructors-Destructors ***/
//Returns a new Graph of size n 
Graph newGraph(int n){
	Graph G = malloc(sizeof (struct GraphObj));
   G->adj = calloc(n + 1, sizeof(List));
   G->color = calloc(n + 1, sizeof(int));
   G->parent = calloc(n + 1, sizeof(int));
   G->discover = calloc(n + 1, sizeof(int));
	G->finish = calloc(n + 1, sizeof(int));
   G->order = n;
   G->size = 0;
	
   for(int i = 1; i <= n; i++) {
      G->adj[i] = newList();
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
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
	free(old->discover);
	free(old->finish);
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

// Returns the parent of vertex u last used in the function BFS(), or NIL if not called yet
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
	if (G == NULL) {
		printf("Cannot call getParent() from NULL Graph reference. \n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Cannot call getParent() with an index not contained in the array. \n");
		exit(1);
	}
	return G->parent[u];
}

// Pre: 1 <= u <= getOrder(G) 
int getDiscover(Graph G, int u){
	if (G == NULL) {
		printf("Cannot call getDiscover() from NULL Graph reference. \n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Cannot call getDiscover() with an index not contained in the array. \n");
		exit(1);
	}
	return G->discover[u];
	
}

/* Pre: 1 <= u <= getOrder(G) */
int getFinish(Graph G, int u){
	if (G == NULL) {
		printf("Cannot call getFinish() from NULL Graph reference. \n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Cannot call getFinish() with an index not contained in the array. \n");
		exit(1);
	}
	return G->finish[u];
} 

/*** Manipulation procedures ***/

// Insert an edge joining u to adjacency List of v and vice versa
// Pre: 1 <= u <= getOrder(G); 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v){
	if (G == NULL) {
		printf("Cannot call addEdge() from NULL Graph reference. \n");
		exit(1);
	}
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
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
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
		printf("Cannot call addArc() with an index not contained in the array. \n");
		exit(1);
	}
	List L = G->adj[u];
	moveFront(L);
	while(index(L) > -1 && v > get(L)) {
		moveNext(L);
   }
	
   if(index(L) == -1) append(L, v);
   else insertBefore(L, v);
	
	G->size++;
}

//Recursively called helper function for DFS, helps determine discover,finish, and color
void Visit(Graph G, List S, int u, int *time){
	G->color[u] = GREY;
	G->discover[u] = ++*time;
	moveFront(G->adj[u]); 
	while (index(G->adj[u]) >= 0) {
		int y = get(G->adj[u]);
		if ( G->color[y] == WHITE ) {
			G->parent[y] = u;
			Visit(G, S, y, time);
		}
		moveNext(G->adj[u]);

	}
	G->color[u] = BLACK;
	G->finish[u] = ++*time;
	prepend(S, u);	
}


// Runs DFS on the Graph G with List S 
// Fills out the color, discover, finish, and parent fields of G aswell
// Pre: length(S)==getOrder(G) 
void DFS(Graph G, List S){
	if (G == NULL) {
		printf("Cannot call DFS() from NULL Graph reference. \n");
		exit(1);
	}
	if(length(S) != getOrder(G)){
		printf("Cannot call DFS() with incorrect sizes \n");
		exit(1);
	}
	
	for(int i = 1; i <= getOrder(G); i++){
		G->color[i] = 	WHITE;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
	}
	int time = 0;
	moveFront(S);
	while(index(S) >= 0){
		int u = get(S);
		if(G->color[u] == WHITE) Visit(G, S, u, &time);
		moveNext(S);
	}
	for(int size = length(S)/2; size > 0; --size) {
		deleteBack(S);
   }
}

/*** Other operations ***/

//Takes a graph in and returns the transpose
Graph transpose(Graph G){
	if(G == NULL){
		printf("Cannot call transpose() from NULL Graph reference. \n");
		exit(1);
	}
   Graph transpose = newGraph(getOrder(G));
	//Same as for copy except int fields are switched
   for(int i = 1; i <= getOrder(G); ++i){
      for(moveFront(G->adj[i]);index(G->adj[i]) >= 0; 
				moveNext(G->adj[i])){
         addArc(transpose, get(G->adj[i]), i);
      }
   }
   return transpose;
}

//Takes a graph in and returns a copy of it
Graph copyGraph(Graph G) {
	if (G == NULL) {
		printf("Cannot call copyGraph() from NULL Graph reference. \n");
		exit(1);
   }
   Graph copy = newGraph(getOrder(G));
   for(int i = 1; i <= getOrder(G); ++i) {
      for(moveFront(G->adj[i]); index(G->adj[i]) >= 0;
				moveNext(G->adj[i])){
         addArc(copy, i, get(G->adj[i])); 
      }
   }
   return copy;
}

//Prints Graph to a file 
void printGraph(FILE* out, Graph G){
	if (out == NULL || G == NULL) {
		printf("Cannot call printGraph() from NULL Graph reference. \n");
		exit(1);
	}
	for(int i = 1; i <= getOrder(G); ++i){
		fprintf(out, "%d: ", i);
		printList(out, G->adj[i]);
		fprintf(out, "\n");	
	}
}
