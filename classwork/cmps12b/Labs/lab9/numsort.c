// $Id: numsort.c,v 1.7 2016-03-10 05:28:59-08 - - $
// Michael Quan miduqan

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>

#include "inssort.h"

char *program_name = NULL;
int exit_status = EXIT_SUCCESS;

int cmpfunc (const void *this, const void *that){
   return ( *(double*)this - *(double*)that);
}

int main(int argc, char **argv){
   (void) argc;
   program_name = basename(argv[0]);

   double array[0x1000];
   size_t count = 0;
   for(;;){
      double number; 
      int scancount = scanf("%lg", &number);
      if(scancount == EOF){
         break;
      }else if(count > 0x1000){
         exit_status = EXIT_FAILURE;
         break;
      }else if(scancount ==1){
         array[count] = number;
         count++;
      }else {
         exit_status = EXIT_FAILURE;
         break;
      }   
   }
   inssort(array, count, sizeof *array, cmpfunc);
   for(size_t index = 0; index < count; index++){
      printf("%20.15g\n", array[index]);
   }

   return exit_status;
}
