// $Id: main.c,v 1.1 2016-02-26 00:58:47-08 - - $
// Michael Quan midquan

#include <assert.h>
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

char *execname = NULL;
int exit_status = EXIT_SUCCESS;

void putinqueue (queue *the_queue, FILE *input, char *filename) {
   char buffer[1024];
   for (int linenr = 1; ; ++linenr) {
      char *linepos = fgets (buffer, sizeof buffer, input);
      if (linepos == NULL) break;
      linepos = strchr (buffer, '\n');
      if (linepos == NULL) {
         fflush (NULL);
         fprintf (stderr, "%s: %s[%d]: unterminated line\n",
                  execname, filename, linenr);
         fflush (NULL);
         exit_status = EXIT_FAILURE;
      }else {
         *linepos = '\0';
      }
      linepos = strdup (buffer);
      assert (linepos != NULL);
      insert_queue (the_queue, linepos);
   }
}

void putfileinqueue (queue *the_queue, char *filename) {
   FILE *input = fopen (filename, "r");
   if (input == NULL) {
      fflush (NULL);
      fprintf (stderr, "%s: %s: %s\n",
               execname, filename, strerror (errno));
      fflush (NULL);
      exit_status = EXIT_FAILURE;
   }else {
      putinqueue (the_queue, input, filename);
      fclose (input);
   }
}


int main (int argc, char **argv) {
   execname = basename (argv[0]);
   queue *the_queue = new_queue();

   if (argc < 2) {
      putinqueue (the_queue, stdin, "-");
   }else {
      for (int argi = 1; argi < argc; ++argi) {
         if (strcmp (argv[argi], "-") == 0) {
            putinqueue (the_queue, stdin, "-");
         }else {
            putfileinqueue (the_queue, argv[argi]);
         }
      }
   }

   while (! isempty_queue (the_queue)) {
      queue_item_t temp = NULL;
      temp = remove_queue(the_queue);
      printf("%s\n",temp);
      free(temp);
   }

   return exit_status;
}

