// $Id: linked_stack.java,v 1.2 2013-11-06 15:14:45-08 - - $
// Michael Walton (mwwalton@ucsc.edu)
// Brandon Butler (bpbutler@ucsc.edu)
//
// NAME
//    class linked_stack - implementation of stack
//

import java.util.NoSuchElementException;

class linked_stack<item_t> {

  private class node {
    item_t value;
    node link;
  }

  private node top = null;

  public boolean empty() {
    return top == null;
  }

  public item_t pop() {
    if (empty()) {
      throw new NoSuchElementException ("linked_stack.pop");
    } else {
      item_t val = top.value;
      top = top.link;
      return val;
    }
  }

  public void push (item_t value) {
    node tmp = new node();
    tmp.link = top;
    tmp.value = value;
    top = tmp;
  }

}

