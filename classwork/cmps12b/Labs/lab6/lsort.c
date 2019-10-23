// $Id: lsort.c,v 1.2 2016-02-19 04:01:50-08 - - $
// Michael Quan midquan

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

typedef struct node_t node_t;
typedef struct list_t list_t;
typedef struct options options;
struct list_t{
   node_t *head;
};
struct node_t {
   char *value;
   node_t *link;
};
struct options{
   bool debug_mode;
};

char *progname = NULL;
int exit_status = EXIT_SUCCESS;

void scan_options (int argc, char **argv, options *opts){
   opts->debug_mode = false;
   opterr = false;
   for(;;){
      int opt = getopt (argc, argv, "d");
      if (opt == EOF) break;
      switch (opt){
         case 'd':
            opts->debug_mode = true;
            break;
         default:
            exit_status = EXIT_FAILURE;
            fflush(NULL);
            fprintf(stderr, "%s: -%c: invalid option\n",
               progname, optopt);
            fflush(NULL);
            break;
      }
   }
}

void insert_ascending(list_t *list, char *val){
   node_t *curr = NULL;
   node_t *prev = NULL;
   curr = list->head;
   
   while(curr != NULL){
      if (strcmp(curr->value, val) > 0) break;
      prev = curr;
      curr = curr->link;
   }
   
   node_t *temp = malloc(sizeof(struct node_t));
   assert(temp != NULL);
   temp->value = val;
   temp->link = curr;
   if (prev == NULL) list->head = temp;
   else prev->link = temp;
}

int main (int argc, char **argv) {
   options opts;
   progname = basename (argv[0]);
   scan_options(argc, argv, &opts);

   list_t *list = malloc(sizeof(struct list_t));
   assert(list != NULL);
   list->head = NULL;
   char buffer[82];
   int linenr;

   for(linenr = 1;;++linenr){
      char *gotline = fgets(buffer, sizeof buffer, stdin);
      if(gotline == NULL) break;

      char *nlpos = strchr(buffer, '\n');
      if (nlpos != NULL){
         *nlpos = '\0';
      }else{
         exit_status = EXIT_FAILURE;
         fflush(NULL);
         fprintf(stderr, "%s: %d: unterminated line: %s\n",
            progname, linenr, buffer);
         fflush(NULL);
      }
      char *value = strdup(buffer);
      assert(value != NULL); 
      insert_ascending(list,value);
   }
   node_t *curr = NULL; 
   for(curr = list->head; curr != NULL;curr = curr->link) {
      if(opts.debug_mode){
         fprintf(stderr,"%s: %p -> node {\n"
                 "    string= %p->\"%s\",\n"
                 "    link= %p }\n",
            progname,curr,curr->value,curr->value,curr->link);
      }else{
          printf ("%s\n", curr->value);
      }

   while(list->head != NULL){
      curr = list->head;
      list->head = curr->link;
      free(curr);
   }

   free(list);
   return exit_status;
   }
}
