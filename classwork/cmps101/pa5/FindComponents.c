// FindComponents.c
// Michael Quan
// midquan
// Programing Assignment 5
// main file for DFS implemeting input and output and finding strongly connected components

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "Graph.h"

#define MAX_LEN 255


int main(int argc, char * argv[]){
	
	
	//Checks to make sure exactly correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s infile outfile\n", argv[0]);
		exit(1);
	}
	// open files for reading and writing
	
	FILE *in, *out;
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if(in == NULL){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if(out == NULL){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
	
	char line[MAX_LEN];
   fgets(line, MAX_LEN, in);
	int size = 0;
   sscanf(line, "%d", &size);
	
	List S = newList();
	for(int x = 1; x <= size; ++x) append(S, x);
	
   Graph G = newGraph(size);
   while(fgets(line, MAX_LEN, in) != NULL)  {
      int a = 0;
      int b = 0;
		//Scans in such a way to pull both ints from the same line and put into a and b
      sscanf(line, "%d %d", &a, &b);
		//End Loop early if 0 0 given
      if(a == 0 && b == 0) break;
      addArc(G, a, b);   
   }
	
	//Print out Adjacency list representation of G 
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n");
	
	//Find Strongly Connect Componenents
	Graph trans = transpose(G);
	DFS(G, S);
	DFS(trans, S);
	
	//Count number of SCC
	int scc = 0;
   for(moveFront(S); index(S) >= 0; 
			moveNext(S)){
		if(getParent(trans, get(S)) == NIL) scc++;
   }

   //Locate Strongly connected componenents
   List strong[scc];
	for(int i = 0; i < scc; i++) {
		strong[i] = newList();
   }
	int count = scc;
	for(moveFront(S); index(S) >= 0; moveNext(S)){
		if(getParent(trans, get(S)) == NIL) count--;
		if(count == scc) break;
		append(strong[count], get(S));
	}
	
	//Print Strongly Connected components
	fprintf(out, "G contains %d strongly connected components:", scc);
	for(int m = 0; m < scc; m++) {
		fprintf(out, "\nComponent %d: ", (m + 1));
		printList(out, strong[m]);
		freeList(&(strong[m]));
   }
   fprintf(out, "\n");
	
	//Free memory used by DFS
   freeList(&S);
	freeGraph(&trans);
   freeGraph(&G);   

   //Close files 
   fclose(in);
   fclose(out);
	
	//Return 0 on exit success
   return(0);
}
