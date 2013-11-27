// $Id: bitree.java,v 1.4 2013-11-06 15:14:45-08 - - $
// Michael Walton (mwwalton@ucsc.edu)
// Brandon Butler (bpbutler@ucsc.edu)
//
// NAME
//    class bitree - starter class for bitree implementation.
//

class bitree {
  char symbol;
  bitree left;
  bitree right;

  bitree (char symbol_, bitree left_, bitree right_) {
    symbol = symbol_;
    left = left_;
    right = right_;
  }

  bitree (char symbol_) {
    this (symbol_, null, null);
  }

  public String toString () {
    if (left == null && right == null){
      return String.valueOf(symbol);
    }else{ 
       String children = right.toString() + symbol + left.toString();
      return "(" + children + ")";
    }
  }

  public double eval(){
    if (left == null && right == null){
      return bitreecalc.table.get_value(symbol);
    } else {
      switch (symbol) {
        case '+':
          return left.eval() + right.eval();
        case '-':
          return left.eval() - right.eval();
        case '*':
          return left.eval() * right.eval();
        case '/':
          return left.eval() / right.eval();
        default:
          auxlib.warn("Invalid Symbol");
          return 0;
      }
    }
  }
}

