// $Id: treemap.java,v 1.22 2016-02-17 09:41:56-08 - - $
// Michael Quan midquan
// Development version of treemap.
// To be deleted and replaced by an actual implementation that
// does *NOT* use java.util.TreeMap.

import static java.lang.System.*;

class treemap {

   class tree {
      String key;
      String value;
      tree left;
      tree right;
      
      //Extra constructor for new trees
      public tree(String key, String value,tree left, tree right){
         this.key = key;
         this.value = value;
         this.left = left;
         this.right = right;
      }
   }
   tree root = null;

   //Binary search to find a given value
   public String get (String key) {
      tree curr = root;
      while (curr != null){
         int cmp = curr.key.compareTo(key);
         if(cmp > 0) curr = curr.left;
         else if(cmp < 0) curr = curr.right;
         else return curr.value;
      }
      return null;
   }

   //Creates a unbalanced tree with given values
   public String put (String key, String value) {
      tree temp = new tree(key,value,null,null);
      if (root == null) {
         root = temp;
         return null;
      }

      tree prev = null;
      tree curr = root;
      boolean shift_lf = true;
      while ( curr != null) {
         int cmp = curr.key.compareTo(key);
         prev = curr;
         if (cmp > 0){
            curr = curr.left;
            shift_lf = true;
         }
         else if (cmp < 0){
            curr = curr.right;
            shift_lf = false;
         }
         else{
            String previous = curr.key;
            curr.key = key;
            return previous;
         }
      }
      if (shift_lf) prev.left = temp;
      else prev.right = temp;
     
      return null;

   }
   
   //Debug methods to help with problems in database/tree
   public void debug_tree () {
      debug_tree_recur (root, 0);
   }

   private void debug_tree_recur (tree node, int depth) {
      if (node != null){
         debug_tree_recur(node.left, depth+1);
         out.printf("%3d \"%s\" \"%s\" %s %s%n", depth, node.key,
            node.value,node.left,node.right);
         debug_tree_recur(node.right, depth+1);            
      }
   }

}
