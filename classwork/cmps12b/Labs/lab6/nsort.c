// $Id: nsort.c,v 1.18 2016-02-19 04:01:53-08 - - $
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
   double number;
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

void insert_ascending(list_t *list, double num){
   node_t *curr = NULL;
   node_t *prev = NULL;
   curr = list->head;
   
   while(curr != NULL){
      if (curr->number > num) break;
      prev = curr;
      curr = curr->link;
   }
   
   node_t *temp = malloc(sizeof(struct node_t));
   assert(temp != NULL);
   temp->number = num;
   temp->link = curr;
   if (prev == NULL) list->head = temp;
   else prev->link = temp;
}

int main (int argc, char **argv) {
   options opts;
   progname = basename (argv[0]);
   scan_options(argc, argv, &opts);

   char err_buffer[256];
   char err_buf_fmt[16];
   sprintf(err_buf_fmt, "%%%lds", sizeof err_buffer -1);
   
   list_t *list = malloc(sizeof(struct list_t));
   assert(list != NULL);
   list->head = NULL;

   for(;;){
      double number;
      int scancount = scanf ("%lg", &number);
      if (scancount == EOF) {
         break;
      }
      //add to node
      else if (scancount == 1){
         insert_ascending(list, number);
      }else{
         scancount = scanf (err_buf_fmt, err_buffer);
         assert (scancount == 1);
         fflush(NULL);
         fprintf (stderr, "%s: bad number \"%s\"\n", progname,
            err_buffer);
         fflush(NULL);
         exit_status = EXIT_FAILURE;
      }
   } 
   node_t *curr = NULL;
   for(curr = list->head; curr != NULL;curr = curr->link) {
      if(opts.debug_mode){
         fprintf(stderr,"%p -> struct node {item=%.15g, link= %p}\n",
            curr,curr->number,curr->link);
      }else{
          printf ("%24.15g\n", curr->number);
      }
   }
   while(list->head != NULL){
      curr = list->head;
      list->head = curr->link;
      free(curr);
   }

   free(list);
   return exit_status;
}
