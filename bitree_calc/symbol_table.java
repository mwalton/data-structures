// $Id: symbol_table.java,v 1.3 2013-10-17 18:33:53-07 - - $
//
//Michael Walton (mwwalton@ucsc.edu)
//Brandon Butler (bpbutler@ucsc.edu)
// NAME
//    class symbol_table
//       Symbol table with letter indices and double and tree values.
//

import static java.lang.System.*;
import static java.lang.String.*;

class symbol_table {

  //
  // Constants for use within this calss.
  //
  private static final char LO_LETTER = 'a';
  private static final char HI_LETTER = 'z';
  private static final int ARRAYLEN = HI_LETTER - LO_LETTER + 1;
  private double[] values = new double[ARRAYLEN];
  private bitree[] trees = new bitree[ARRAYLEN];

  //
  // Convert letter into array index.
  //
  private int aindex (char varname) {
    int index = Character.toLowerCase (varname) - LO_LETTER;
    if (index < 0 || index >= ARRAYLEN) {
      throw new IndexOutOfBoundsException (
          format ("'%c' is out of bounds: '%c'..'%c'",
            varname, LO_LETTER, HI_LETTER));
    }
    return index;
  }

  //
  // Constructor.  Defaults all values to NaN.
  //
  public symbol_table() {
    for (int index = 0; index < values.length; ++index) {
      values[index] = Double.NaN;
    }
  }

  //
  // Accessors.  Get the value or the tree from the symbol table.
  //
  public double get_value (char varname) {
    return values[aindex (varname)];
  }

  public bitree get_tree (char varname) {
    return trees[aindex (varname)];
  }

  //
  // Mutators.  Change the value and the tree in the table.
  //
  public void put (char varname, double value, bitree tree) {
    int index = aindex (varname);
    values[index] = value;
    trees[index] = tree;
  }

  public String toString() {
    String table_dump = "******Final Symbol Table********\n";
    for (int i = 0; i < values.length; ++i) {
      if (values[i] != Double.NaN  && trees[i] !=null) {
        String treeString = trees[i].toString();
        String valueString = "" + values[i];

        table_dump += table_dump+valueString+" = "+treeString+"\n";
      }
    }
    return table_dump;
  }
}
