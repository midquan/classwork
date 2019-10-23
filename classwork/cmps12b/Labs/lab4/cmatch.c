// $Id: cmatch.c,v 1.30 2016-02-08 21:26:26-08 - - $
//
// NAME Michael Quan midquan
//
//    cmatch - print matching lines from files 
//
// SYNOPSIS
//    cmatch [-iln] string [filename...]
//
// DESCRIPTION
//    Searches the named input files for lines containing string
//    By default, matching lines are printed.
//    If more than one file is specified, lines of output are
//    preceded by the filename.

#define _GNU_SOURCE
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>


char *program_name = NULL;
int exit_status = EXIT_SUCCESS;
int file_count = 0;
#define STDIN_NAME "-"

typedef struct options {
   bool ignore_case;
   bool filenames_only;
   bool number_lines;
} options;

void scan_options (int argc, char **argv, options *opts) {
   opts->ignore_case = false;
   opts->filenames_only = false;
   opts->number_lines = false;
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "iln");
      if (opt == EOF) break;
      switch (opt) {
         case 'i':
            opts->ignore_case = true;
            break;
         case 'l':
            opts->filenames_only = true;
            break;
         case 'n':
            opts->number_lines = true;
            break;
         default:
            exit_status = EXIT_FAILURE;
            fflush (NULL);
            fprintf (stderr, "%s: -%c: invalid option\n",
                             program_name, optopt);
            break;
      }
   }
}


const char *strbool (bool value) {
   return value ? "true" : "false";
}

void catbyline(FILE *input, char *filename,char *target,options *opts){
   char buffer[1024];
   for (int linenr = 1;; ++linenr) {
      char *buf = fgets (buffer, sizeof buffer, input);
      if (buf == NULL) break;
      if(opts->ignore_case){
         if(strcasestr(buf, target)!= NULL){
            if(opts->filenames_only){
               printf("%s \n", filename);
               break;
            }else{
               if(opts->number_lines){
                  if(file_count > 1){
                     printf("%s:%d:%s", filename, linenr, buf); 
                  }else {
                     printf("%d:%s", linenr, buf);
                  }
               }
               else{
                  if(file_count > 1){
                     printf("%s:%s",filename, buf); 
                  }else{
                      printf("%s",buf);
                  }  
           
               }
            }
         }
      }else{
         if(strstr(buf, target) != NULL){
            if(opts->filenames_only){
               printf("%s", filename);
               break;
            }else{
               if(opts->number_lines){
                  if(file_count > 1){
                     printf("%s:%d:%s", filename, linenr, buf);
                  }else{
                      printf("%d:%s", linenr, buf);
                  }
               }else{
                  if(file_count > 1){
                     printf("%s:%s",filename, buf);
                  }else{ 
                     printf("%s",buf);
                  }
               }
            }
         }
            
      }
   }
}

int main (int argc, char **argv) {
   program_name = basename (argv[0]);
   options opts;
   scan_options(argc, argv, &opts);
   
   if (argc == 1) {
      exit_status = EXIT_FAILURE;
      fflush (NULL);
      fprintf(stderr, "Usage: %s [-iln] string  [filename...] \n"
         , program_name);
      fflush (NULL);
   }else {
      file_count = argc - (optind + 1);
      for (int argi = optind +1; argi < argc; ++argi) {
         char *target = argv[optind];
         char *filename = argv[argi];
         if (strcmp (filename, STDIN_NAME) == 0) {
            catbyline (stdin, STDIN_NAME,target,&opts);
         }else {
            FILE *input = fopen (filename, "r");
            if (input != NULL) {
               catbyline (input, filename,target,&opts);
               fclose (input);
            }else {
               exit_status = EXIT_FAILURE;
               fflush (NULL);
               fprintf (stderr, "%s: %s: %s\n", program_name,
                        filename, strerror (errno));
               fflush (NULL);
            }
         }
      }
   }
   return exit_status;
}
