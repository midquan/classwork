// Lex.java
// Michael Quan
// midquan
// Programing Assignment 2
// Parses inputs and outputs an alphabetized list

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "List.h"

#define MAX_LEN 255

int main(int argc, char * argv[]){

   int count = 0;
   FILE *in, *out;
   char line[MAX_LEN];

   // check command line for correct number of arguments
   if( argc != 3 ){
      fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   /* read each line of input file, then count and print tokens */
   while( fgets(line, MAX_LEN, in) != NULL)  {
      count++;
   }
	
	rewind(in);

	char lines[count - 1][MAX_LEN];
   int ln = -1;
   // Loop through and copy the file lines into a string array
   while(fgets(line, MAX_LEN, in) != NULL) {
      strcpy(lines[++ln], line);
   }
	List linked = newList();
	
	append(linked, 0);
	
	//Start the Pseudo-Insertion Sort
	for(int i = 1; i<count;i++){
		char *temp = lines[i];
		int j = i - 1;
		
		//Start from end of list
		moveBack(linked);
		
		//Work backwards
		while(j >= 0 && strcmp(temp,lines[get(linked)]) <= 0){
			--j; 
			movePrev(linked);
		}
		if(index(linked) >= 0) insertAfter(linked,i);
		else prepend(linked,i);
	}
	moveFront(linked);
	
	//Write the output file after sorted indexes
	while(index(linked) >= 0) {
      fprintf(out, "%s", lines[get(linked)]);
      moveNext(linked);
	}
	 /* close files */
	
   fclose(in);
   fclose(out);
	
	//Free List
	freeList(&linked);
   return(0);
}