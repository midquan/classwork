// Graph.c
// Michael Quan
// midquan
// Programing Assignment 4
// main file for BFS implemeting input and output

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
	
   Graph G = newGraph(size);
   while(fgets(line, MAX_LEN, in) != NULL)  {
      int a = 0;
      int b = 0;
		//Scans in such a way to pull both ints from the same line and put into a and b
      sscanf(line, "%d %d", &a, &b);
		//End Loop early if 0 0 given
      if(a == 0 && b == 0) break;
      addEdge(G, a, b);   
   }
	printGraph(out, G);
	
	int count = 0;
	while( fgets(line, MAX_LEN, in) != NULL)  {
      int a = 0;
      int b = 0;
      sscanf(line, "%d %d", &a, &b);
      if(a == 0 && b == 0) break;
		
		if(count++ != 0) fprintf(out, "\n");
		fprintf(out, "\n");
		BFS(G, a);
      int d = getDist(G, b);
      fprintf(out, "The distance from %d to %d is ", a, b);
		
		
      if(d == INF) fprintf(out, "infinity\n");
      else fprintf(out, "%d\n", d);
		
      List P = newList();
      getPath(P, G, b);
		
      if(front(P) == NIL) fprintf(out, "No %d-%d path exists", a, b);
      else {
         fprintf(out, "A shortest %d-%d path is: ", a, b);
         printList(out, P);
      }
      freeList(&P);
   }
	   fprintf(out, "\n");
   freeGraph(&G);   

   /* close files */
   fclose(in);
   fclose(out);
   return(0);
}