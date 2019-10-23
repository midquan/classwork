// $Id: stacktrace.c,v 1.3 2015-03-06 14:58:36-08 - - $

// Show how the "where" command works at a crash.

#include <stdio.h>

void crash (char** arg) {
   printf ("%s\n", *arg);
   crash (&arg[1]);
}

int main (int argc, char**argv) {
   (void) argc;
   crash (argv);
   return 0;
}

