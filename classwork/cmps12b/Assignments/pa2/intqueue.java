// $Id: intqueue.java,v 1.12 2016-02-02 03:56:32-08 - - $
// Michael Quan midquan 
// Jourdyn Calhoun jacalhou

import java.util.Iterator;
import java.util.NoSuchElementException;

class intqueue implements Iterable<Integer> {

   private class node {
      int linenr;
      node link;
   }
   private int count = 0;
   private node front = null;
   private node rear = null;

   public void insert (int number) {
      ++count;
      //FIXME
      //Pushes the node to insert new numbers 
      node new_node = new node();
      new_node.linenr = number;
      new_node.link = null;
      if(front == null){
         front = new_node;
         rear = front;
      }else{
         rear.link = new_node;
         rear = rear.link;
      }

   }

   public boolean empty() {
      return count == 0;
   }

   public int getcount() {
      return count;
   }

   public Iterator<Integer> iterator() {
      return new iterator();
   }

   private class iterator implements Iterator<Integer> {
      node curr = front;

      public boolean hasNext() {
         return curr != null;
      }

      public Integer next() {
         if (curr == null) throw new NoSuchElementException();
         Integer next = curr.linenr;
         curr = curr.link;
         return next;
      }

      public void remove() {
         throw new UnsupportedOperationException();
      }
   }

}

