// $Id: jxref.java,v 1.44 2016-02-02 03:56:32-08 - - $
// Michael Quan midquan
// Jourdyn Calhoun jacalhou
import java.io.*;
import java.util.Iterator;
import java.util.Map.Entry;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import static java.lang.System.*;

class jxref {
   private static final String STDIN_FILENAME = "-";
   private static final String REGEX = "\\w+([-'.:/]\\w+)*";
   private static final Pattern PATTERN = Pattern.compile(REGEX);

   private static void xref_file (String filename, Scanner file){
      listmap map = new listmap();
      for (int linenr = 1; file.hasNextLine(); ++linenr) {
         String line = file.nextLine();
         Matcher match = PATTERN.matcher (line);
         while (match.find()) {
            String word = match.group();
            //FIXME
            map.insert(word, linenr);
         }
      }
      //Creates semi-colon spacing and puts filename 
      for (int i= 0; i<65; i++){
         if(i==32) out.printf("%n%s%n", filename);
         else out.printf(":");
      }
      out.printf("%n");

      for (Entry<String, intqueue> entry: map) {
         //FIXME
         out.printf("%s [%d]",entry.getKey(),
            entry.getValue().getcount()); 
         //Iterates to print multiple line numbers
         for (Iterator<Integer> ln_iterator=entry.getValue().iterator();
               ln_iterator.hasNext();) {
            out.printf(" %d", ln_iterator.next());
         }
         out.printf("%n");
      }
         
      
   }

 
   // For each filename, open the file, cross reference it,
   // and print.
   private static void xref_filename (String filename) {
      if (filename.equals (STDIN_FILENAME)) {
         xref_file (filename, new Scanner (System.in));
      }else {
         try {
            Scanner file = new Scanner (new File (filename));
            xref_file (filename, file);
            file.close();
         }catch (IOException error) {
            misc.warn (error.getMessage());
         }
      }
   }

   // Main function scans arguments to cross reference files.
   public static void main (String[] args) {
      if (args.length == 0) {
         xref_filename (STDIN_FILENAME);
      }else {
         for (String filename: args) {
            xref_filename (filename);
         }
      }
      exit (misc.exit_status);
   }

}

