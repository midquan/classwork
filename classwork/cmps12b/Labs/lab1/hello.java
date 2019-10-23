// $Id: hello.java,v 1.9 2016-01-15 01:43:45-08 - - $
// Michael Quan midquan
class hello {
   public static void main(String [] args){
      if(args.length == 0){
         System.out.println("Hello, World!");
         System.exit(0);
      }
      else{
         System.err.println("Usage: hello");
         System.exit(1);
      }
   }
} 
