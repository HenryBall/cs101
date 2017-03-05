// Lex.java
// Henry Ball
// hfball
// pa1
// This program indirectly sorts an array of strings using a doubly linked list

import java.io.*;
import java.util.Scanner;

class Lex{
   public static void main(String[] args) throws IOException{
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      int i = 0, n = 0, j;
      List L = new List();

      // args must be of length 2
      if(args.length < 2){
         System.err.println("Usage: FileIO infile outfile");
         System.exit(1);
      }

      BufferedReader reader = new BufferedReader(new FileReader(args[0]));
      while(reader.readLine() != null) n++;
      reader.close();
      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));

      String[] input = new String[n];
   
      // populate array with the lines of the input file
      while(in.hasNextLine()){
         line = in.nextLine();
         input[i] = line;
         i++;
      }

      indirectSort(input, L);
      L.moveFront();
      // print input array by the idices stored in the list
      for(j=0; j<L.length(); j++){
         out.println(input[L.get()]);
         L.moveNext();
      }
      
      in.close();
      out.close();

   }

   public static void indirectSort(String[] A, List L){
      L.append(0); // begin by appending the 0th index
      for(int j=1; j<A.length; j++){ // insert indices 1-n
         L.moveFront(); // begin with the cursor at the front of the list
         while(L.index() > -1 && A[j].compareTo(A[L.get()])>0){
            L.moveNext(); // iterate over the array until the cursor falls off the list or the proper place for the current index is found
         }
         if(L.index() == -1){
            L.append(j);
         }else if(L.index() == 0){
            L.prepend(j);
         }
         else{
            L.insertBefore(j);
         }
      }
   }
}
