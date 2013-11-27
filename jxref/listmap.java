// Michael Walton (mwwalton@ucsc.edu)
// Brandon Butler (bpbutler@ucsc.edu)
// $Id: listmap.java,v 1.19 2013-10-27 17:16:22-07 - - $

import java.util.Iterator;
import java.util.Map.Entry;
import java.util.NoSuchElementException;
import static java.lang.System.*;

class listmap implements Iterable<Entry<String,intqueue>> {

   private class node implements Entry<String,intqueue> {
      String key;
      intqueue queue = new intqueue();
      node link;
      public String getKey() {
         return key;
      }
      public intqueue getValue() {
         return queue;
      }
      public intqueue setValue (intqueue queue) {
         throw new UnsupportedOperationException();
      }
   }
   private node head = null;

   public listmap() {
      // Not needed, since head defaults to null anyway.
   }

   public void insert (String key, int linenr) {
      //FIXME
      //<mwwalton>
      node curr = head;
      node prev = null;
      int compare = 1;

      //phase 1: locate insertion point
      while (curr != null) {
         compare = curr.key.compareTo(key);
         if (compare >= 0) break;
         prev = curr;
         curr = curr.link;
      }
      //Phase 2: insert the key (if not already there)
      if (compare != 0) {
         node tmp = new node();
         tmp.key = key;
         tmp.link = curr;
         if (prev == null) {
            head = tmp;
         } else {
            prev.link = tmp;
         }
      }
      if (prev == null) {
         head.queue.insert(linenr);
      } else {
         prev.link.queue.insert(linenr);
      }
      //</mwwalton>
   }

   public Iterator<Entry<String,intqueue>> iterator() {
      return new iterator();
   }


   private class iterator
           implements Iterator<Entry<String,intqueue>> {
      node curr = head;

      public boolean hasNext() {
         return curr != null;
      }

      public Entry<String,intqueue> next() {
         if (curr == null) throw new NoSuchElementException();
         node next = curr;
         curr = curr.link;
         return next;
      }

      public void remove() {
         throw new UnsupportedOperationException();
      }

   }

}
