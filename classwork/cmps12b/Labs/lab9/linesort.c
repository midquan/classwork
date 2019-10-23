// $Id: linesort.c,v 1.7 2016-03-10 05:45:31-08 - - $
// Michael Quan miduqan

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <assert.h>

#include "inssort.h"

char *program_name = NULL;
int exit_status = EXIT_SUCCESS;

int cmpfunc(const void *this, const void *that) {

   char **thisstr = (char**) this;
   char **thatstr = (char**) that;
   return strcmp(*thisstr, *thatstr);
}

int main(int argc, char **argv){
   (void) argc;
   program_name = basename(argv[0]);

   char *array[0x1000];
   char buffer[0x1000];
   size_t linenr = 1;
   for(;;linenr++){
      char *linepos = fgets(buffer, sizeof buffer, stdin); 
      if (linepos == NULL) break;
      if (linenr - 1 > 0x1000) break;
      linepos = strchr (buffer, '\n');
      *linepos = '\0';
      linepos = strdup(buffer);
      assert (linepos != NULL);
      array[linenr - 1] = linepos;
   }

   inssort(array, linenr - 1, sizeof *array, cmpfunc);
   for(size_t index = 0; index < linenr - 1; index++){
      printf("%s\n", array[index]);
      free(array[index]);
   }

   return exit_status;
}
