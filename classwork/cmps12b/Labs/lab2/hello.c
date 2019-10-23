// $Id: hello.c,v 1.3 2016-01-21 16:29:25-08 - - $
// Michael Quan midquan
//
// NAME
//    hello - print the "Hello, World!" message.
//
// SYNOPSIS
//    hello
//
// DESCRIPTION
//    Prints the "Hello, World!" message if no operands are
//    present.  Errors out with a Usage message otherwise.
//

#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
   int exit_status = EXIT_SUCCESS;
   char* prog_name = basename(argv[0]);
  
   if(argc == 1){
      printf ("Hello, World!\n");
   }else{
      fprintf (stderr, "Usage: %s\n", prog_name);
      exit_status = EXIT_FAILURE;
   }
   return exit_status;
}

