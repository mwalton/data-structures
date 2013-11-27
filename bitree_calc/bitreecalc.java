// $Id: bitreecalc.java,v 1.2 2013-11-06 15:14:45-08 - - $
// Michael Walton (mwwalton@ucsc.edu)
// Brandon Butler (bpbutler@ucsc.edu)

import java.io.*;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import static java.lang.System.*;

class bitreecalc {
  private static final String STDIN_FILENAME = "-";
  public static linked_stack stack = new linked_stack();
  public static symbol_table table = new symbol_table();
  public static boolean echoOpt = false;
  public static boolean outputOpt = false;
  public static String outFile;

  static void writefile (String filename) {
    try{
      PrintStream writer = new PrintStream (new File (filename));
      writer.printf ("%s",table);
    } catch (IOException err) {
      auxlib.warn("%s", err.getMessage());
    }
  }

  private static void parseLn (String line) {
    char var = line.charAt(0);
    if (isLetter(var)){
      char opr = line.charAt(1);
      switch (opr) {
        case '=':
          equalsOp(var, line);
          break;
        case ':':
          String value = line.split(":")[1];
          try {
            double val = Double.parseDouble(value);
            bitree tree = null;
            table.put(var, val, tree);
            printEcho(var, tree);

          } catch (NumberFormatException err) {
            auxlib.warn(err.getMessage());
          }
          break;
        case '?':
          bitree tree = table.get_tree(var);
          printEcho(var, tree);
          break;
        default:
          auxlib.warn("Not an expression");
          break;
      }
    }else{
      auxlib.warn("Not a letter");
    }
  }

  /* public static String fmt(double value){
     if (value == (int)value){
     return String.format("%d", (int)value);
     }else{
     return String.format("%s",value);
     }
     }*/

  private static void printEcho(char var, bitree tree){
   // if (echoOpt) {
      out.printf("%s: %s%n", var, table.get_value(var));
      out.printf("   %s%n", tree);
   // }
  }

  private static void equalsOp(char var, String line) {
    String expression = line.split("=")[1];
    if (!validExp(expression)) {
      auxlib.warn("Not an expression");
    } else {
      stack = new linked_stack();
      for (int i = 0; i < expression.length(); ++i) {
        char curr = expression.charAt(i);
        if (isOpr(curr)) {
          bitree left = (bitree) stack.pop();
          bitree right = (bitree) stack.pop();

          bitree tmp = new bitree(curr, left, right);
          stack.push(tmp);
        } else {
          bitree tmp = new bitree(curr);
          stack.push(tmp);
        }
      }
      bitree tree = (bitree) stack.pop();
      if (stack.empty()) {
        double val = tree.eval();
        table.put(var, val, tree);
      } else {
        auxlib.warn("Stack not empty");
      }
      printEcho(var, tree);
    }
  }
  private static boolean isLetter(char c){
    if (Character.isLetter(c) == false){
      return false;
    }else{
      return true;
    }
  }

  private static boolean isOpr(char c) {
    return c == '+' || c == '*' || c == '/' || c == '-';
  }

  private static boolean validExp(String ex) {
    //FIX ME
    if (ex.trim().length() == 0 ) {
      return false;
    } else {
      return true;
    }
  }

  private static void calc_file (String filename, Scanner file) {
    while(file.hasNextLine()) {
      String line = file.nextLine();
      line = line.trim().replaceAll("\\s+","");
      parseLn(line);
    }
  }

  private static void calc_filename (String filename) {
    if (filename.equals(STDIN_FILENAME)) {
      calc_file(filename, new Scanner(System.in));
    } else {
      try {
        Scanner file = new Scanner(new File(filename));
        calc_file(filename, file);
        file.close();
      } catch (IOException err) {
        auxlib.warn(err.getMessage());
      }
    }
  }

  public static void parseArgs(String[] args) {
    int opts = 0;
    for (int i = 0; i < args.length; ++i) {
      if (args[i].indexOf("-e") >=0) {
        echoOpt = true;
        opts++;
      }
      if (args[i].indexOf("-o") >=0) {
        outputOpt = true;
        outFile = args[++i];
        opts += 2;
      }

      String files[] = new String[args.length - opts];
      arraycopy(args, opts, files, 0, files.length);

      for (String filename : files) {
        calc_filename(filename);
      }
    }
  }
  public static void main (String[] args) {
    if (args.length == 0) {
      calc_filename(STDIN_FILENAME);
    } else {
      parseArgs(args);
      if (outputOpt) {
        writefile(outFile);
      }
    }
  }
}

