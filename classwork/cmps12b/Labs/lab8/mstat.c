// $Id: mstat.c,v 1.10 2016-03-03 01:30:03-08 - - $
// Michael Quan midquan

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <libgen.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <utime.h>
#include <locale.h>

int exit_status = EXIT_SUCCESS;
char *program_name = NULL;


void print_stat(char *filename){
   struct stat st;
   int value = lstat(filename, &st);
   time_t time_diff = (time_t) 180 * 24 * 60 * 60;
   if(value == 0){
      printf("%6o %9jd", st.st_mode, st.st_size);
      
      time_t old_time = st.st_mtime;
      time_t curr_time = time(NULL);
      struct tm *tm = localtime(&old_time);
      char buff[256];
      char *timefmt = NULL;
      if(curr_time - old_time < time_diff){
         timefmt = "%b %e %R";
      }else{
         timefmt = "%b %e  %Y";
      }
      strftime(buff, sizeof buff, timefmt, tm);
      printf(" %s", buff);

      printf(" %s", filename);
      char buffer[1024];
      ssize_t symlink = readlink(filename, buffer, sizeof buffer);
      if (symlink != -1) {
         printf(" -> %s", buffer);
      }
      printf("\n");
   }else{
      exit_status = EXIT_FAILURE;
      fflush(NULL);
      fprintf(stderr, "%s: %s: %s\n", program_name,
         filename, strerror(errno));
      fflush(NULL);
   }
}

int main(int argc, char **argv){
   program_name = basename(argv[0]);
   setlocale(LC_NUMERIC, "en_US");
   if(argc == 1){
      char *filename = ".";
      print_stat(filename);
   }
   else{
      for(int argi = 1; argi < argc; argi++){
         char *filename = argv[argi];
         print_stat(filename);
      }
   }
   return exit_status;
}
