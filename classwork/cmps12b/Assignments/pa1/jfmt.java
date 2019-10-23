// $Id: jfmt.java,v 1.48 2016-01-20 12:16:12-08 - - $
// Michael Quan midquan
// This program is the jfmt utility which takes a file and reformats it to
// either the given width or the default width -65 and concatenizes
// the white space also prints an error if bad inputs.
//

import java.io.*;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import static java.lang.System.*;


class jfmt {
   // Static variables keeping the general status of the program.
   public static final String JAR_NAME = get_jarname();
   public static final int EXIT_SUCCESS = 0;
   public static final int EXIT_FAILURE = 1;
   public static int exit_status = EXIT_SUCCESS;
   public static int width = 65;
   // A basename is the final component of a pathname.
   // If a java program is run from a jar, the classpath is the
   // pathname of the jar.
   static String get_jarname() {
      String jarpath = getProperty ("java.class.path");
      int lastslash = jarpath.lastIndexOf ('/');
      if (lastslash < 0) return jarpath;
      return jarpath.substring (lastslash + 1);
   }


   // Formats a single file.
   static void format (Scanner infile) {
      // Read each line from the opened file, one after the other.
      // Stop the loop at end of file.
      List<String> words = new LinkedList<String>();
      for (int linenr = 1; infile.hasNextLine(); ++linenr) {
         String line = infile.nextLine();
         // Create a LinkedList of Strings.

         // Split the line into words around white space and iterate
         // over the words.
         for (String word: line.split ("\\s+")) {

            // Skip an empty word if such is found.
            if (word.length() == 0) continue;
            words.add (word);
            
         }
      }
      print_paragraph(words);
      out.printf("%n");
   }
   static void print_paragraph(List<String> words){
      int count = 0;
      for(String word: words){
         if(count == 0){
            out.printf("%s",word);
            count += word.length();
         }  
         else{
            count += 1 + word.length();
            if(count>width){
               out.printf("%n");
               out.printf(word);
               count = word.length();
            }
            else out.printf(" %s",word);
         }
      }  
      words.clear();
   }   


   // Main function scans arguments and opens/closes files.
   public static void main (String[] args) {
      if (args.length == 0) {
         // There are no filenames given on the command line.
         err.printf ("Usage: jfmt [-width] [filename...]");
         err.printf ("%n");
         System.exit(1);
      }
      else {
         if(args[0].substring(0).equals("-")){
            String begin = args[0];
            String num = begin.substring(1,begin.length()-1);
            width = Integer.parseInt(num);
         }
         
         // Iterate over each filename given on the command line.
         for (int argix = 0; argix < args.length; ++argix) {
            String filename = args[argix];
            if (args[0].substring(0).equals ("-")) {
               // Treat a filename of "-" to mean System.in.
               String begin = args[0];
               String num = begin.substring(1,begin.length()-1);
               width = Integer.parseInt(num);
               out.printf ("FILE: -%n");
               format (new Scanner (in));
            }else {
               // Open the file and read it, or error out.
               try {
                  Scanner infile = new Scanner (new File (filename));
                 // out.printf ("FILE: %s%n", filename);
                  format (infile);
                  infile.close();
               }catch (IOException error) {
                  exit_status = EXIT_FAILURE;
                  err.printf ("%s: %s%n", JAR_NAME,
                              error.getMessage());
               }
            }
         }
      }
      out.printf("%n");
      exit (exit_status);
   }

}
