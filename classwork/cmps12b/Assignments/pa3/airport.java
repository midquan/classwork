// $Id: airport.java,v 1.22 2016-02-17 09:37:56-08 - - $
// Michael Quan midquan
//
// Based off of starter code given then added code to fit
// specifications given by the assignment.
//

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class airport {
   private static final String STDIN_FILENAME = "-";

   public static treemap load_database (String database_name) {
      treemap tree = new treemap ();
      try {
         Scanner database = new Scanner (new File (database_name));
         for (int linenr = 1; database.hasNextLine(); ++linenr) {
            String line = database.nextLine();
            if (line.matches ("^\\s*(#.*)?$")) continue;
            String[] keyvalue = line.split (":");
            if (keyvalue.length != 2) {
               misc.warn (database_name, linenr, "invalid line");
               continue;
            }
            tree.put (keyvalue[0], keyvalue[1]);
         }
         database.close();
      }catch (IOException error) {
         misc.warn (error.getMessage());
      }
      return tree;
   } 

   public static void main (String[] args) {
      int args_count = 0;
      boolean debug_opt = false;
      //Try Catch for valid inputs
      try{
         if(args[0].substring(0,1).equals("-")){
            if(args[args_count].equals("-d")){
               debug_opt = true;
            }
            else{
               misc.warn("airport not found");
            }
            args_count++;
         }
      }
      //Exception and Exit if bad input
      catch(Exception e){
         misc.die("Usage: airport [-d] database");
      }
      treemap tree = load_database (args[args_count]);
      
      //Turns on Debug mode
      if(debug_opt){ 
         tree.debug_tree ();
      }
      //Searches for airports in database
      else{
         Scanner stdin = new Scanner (in);
         while (stdin.hasNextLine()) {
            String airport = stdin.nextLine().toUpperCase().trim();
            String airport_name = tree.get (airport);
            if (airport_name == null) {
               misc.warn("airport not found");
            }
            else if(airport.matches ("^\\s*(#.*)?S")) continue;
            else {
               out.printf ("%s = %s%n", airport, airport_name);
            }
         }
      }  
      exit (misc.exit_status);
   }
}
