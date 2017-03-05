// Sparse.java
// Henry Ball
// hfball
// pa3
// does calculations on sparse matrices 

import java.io.*;
import java.util.Scanner;

class Sparse{
   public static void main(String[] args) throws IOException{
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      String[] token = null;

      if(args.length < 2){
         System.err.println("Usage: FileIO infile outfile");
         System.exit(1);
      }

      in = new Scanner(new File(args[0]));

      line = in.nextLine()+" ";
      token = line.split("\\s+");
      Matrix x = new Matrix(Integer.parseInt(token[0]));
      Matrix y = new Matrix(Integer.parseInt(token[0]));
      int a = Integer.parseInt(token[1]);
      int b = Integer.parseInt(token[2]);

      //in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));

      int lineNum = 1;
      while(in.hasNextLine()){
         lineNum++;
         line = in.nextLine()+" ";
         token = line.split("\\s+");
         if(lineNum > 2 && lineNum <= a+2){
            x.changeEntry(Integer.parseInt(token[0]), Integer.parseInt(token[1]), Double.parseDouble(token[2]));
         }
         if(lineNum > a+3  && lineNum <= b+a+4){
            y.changeEntry(Integer.parseInt(token[0]), Integer.parseInt(token[1]), Double.parseDouble(token[2]));
         }
      }

      out.println("A has " + x.getNNZ() + " non-zero entries:");
      out.println(x);

      out.println("B has " + y.getNNZ() + " non-zero entries:");
      out.println(y);

      out.println("(1.5)*A = ");
      out.println(x.scalarMult(1.5));

      out.println("A+B = ");
      out.println(x.add(y));

      out.println("A+A = ");
      out.println(x.add(x));

      out.println("B-A = ");
      out.println(y.sub(x));

      out.println("A-A = ");
      out.println(x.sub(x));

      out.println("Transpose(A) = ");
      out.println(x.transpose());

      out.println("A*B = ");
      out.println(x.mult(y));

      out.println("B*B = ");
      out.println(y.mult(y));
      
      in.close();
      out.close();
   }
}
