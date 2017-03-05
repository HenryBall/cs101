// Matrix.java
// Henry Ball
// hfball
// pa3
// Matrix calculator built upon the linked list ADT

class Matrix{
   // Private Entry class ------------------------------------------------------
   private class Entry{
      int col;
      double val;

      Entry(int col, double val){
         this.col = col;
         this.val = val;
      }

      public boolean equals(Object x){
         boolean eq = false;
         Entry k;
         if(x instanceof Entry){
            k = (Entry)x;
            eq = (this.col == k.col && this.val == k.val);
         }
         return eq;
      }

      public String toString(){
         return "(" + col + ", " + val + ")";
      }
   }

   // Constructor --------------------------------------------------------------
   List[] row;
   Matrix(int n){
      if(n < 1){
         throw new RuntimeException("Matrix Error: Matrix() constructor must be called with a row/column count greater than 0");
      }
      row = new List[n+1];
      for(int i=1; i < n+1; i++){
         row[i] = new List();
      }
   }

   // Access functions ---------------------------------------------------------
   
   // getSize()
   // returns the number of rows and columns of this matrix
   int getSize(){
      return row.length - 1;
   }

   // getNNZ()
   // returns number of non zero elements in this matrix
   int getNNZ(){
      int NNZ = 0;
      for(int i=1; i<=getSize(); i++){
         NNZ += row[i].length();
      }
      return NNZ;
   }

   // equals()
   // overrides objects equals() method
   public boolean equals(Object x){
      Matrix k;
      if(x instanceof Matrix){
         k = (Matrix)x;
         if(getSize() != k.getSize()){
            return false;
         }
         for(int i=1; i<=getSize(); i++){
            if(!(row[i].equals(k.row[i]))){
               return false;
            }
         }
      }
      return true;
   }

   // Manipulation procedures --------------------------------------------------

   // makeZero()
   // returns this matrix to the zero state
   void makeZero(){
      for(int i=1; i<=getSize(); i++){
         row[i].clear();
      }
   }

   // copy()
   // returns a copy of this matrix
   Matrix copy(){
      Matrix out = new Matrix(getSize());
      for(int i=1; i<=getSize(); i++){
         row[i].moveFront();
         while(row[i].index() != -1){
            Entry current = (Entry)row[i].get();
            out.row[i].append(new Entry(current.col, current.val));
            row[i].moveNext();
         }
      }
      return out;
   }

   // changeEntry()
   // changes the ith row and jth column of this matrix to x
   // pre: 1<=i<=getSize(), 1<=j<=getSize()
   void changeEntry(int i, int j, double x){
      if(i<1 || i>getSize() || j<1 || j>getSize()){
         throw new RuntimeException("Matrix Error: calling changeEntry() with invalid arguments");
      }

      row[i].moveFront();
      while(row[i].index() != -1){
         Entry current = (Entry)row[i].get();
         if(current.col == j){
            if(x == 0.0){
               row[i].delete();
               return;
            }else{
               current.val = x;
               return;
            }
         }
         if(current.col > j && x != 0.0){
            if(row[i].index() == 0){
               row[i].prepend(new Entry(j, x));
               return;
            }else{
               row[i].insertBefore(new Entry(j, x));
               return;  
            }
         }
         row[i].moveNext();
      }
      if(x != 0.0){
         row[i].append(new Entry(j, x)); 
      }
   }

   // scalarMult()
   // multiplies this matrix by a constant x
   Matrix scalarMult(double x){
      Matrix out = new Matrix(getSize());
      for(int i=1; i<=getSize(); i++){
         row[i].moveFront();
         while(row[i].index() != -1){
            Entry current = (Entry)row[i].get();
            out.changeEntry(i, current.col, current.val*x);
            row[i].moveNext();
         }
      }
      return out;
   }

   // add()
   // adds this matrix to matrix M
   // pre: getSize() == M.getSize()
   Matrix add(Matrix M){
      if(getSize() != M.getSize()){
         throw new RuntimeException("Matrix Error: cannot add matrices of different sizes.");
      }

      Matrix out = new Matrix(getSize());
      if(this.equals(M)){
         out = this.scalarMult(2.0);
         return out;
      }
      for(int i=1; i<=getSize(); i++){
         row[i].moveFront();
         M.row[i].moveFront();
         while(row[i].index() != -1 || M.row[i].index() != -1){
            if(row[i].index() != -1 && M.row[i].index() != -1){
               Entry x = (Entry)row[i].get();
               Entry y = (Entry)M.row[i].get();
               if(x.col == y.col && (x.val != 0.0 && y.val != 0.0)){
                  out.row[i].append(new Entry(x.col, x.val + y.val));
                  row[i].moveNext();
                  M.row[i].moveNext();
               }else if(x.col > y.col){
                  out.row[i].append(new Entry(y.col, y.val));
                  M.row[i].moveNext();
               }else if(x.col < y.col){
                  out.row[i].append(new Entry(x.col, x.val));
                  row[i].moveNext();
               }
            }else if(row[i].index() != -1){
               Entry x = (Entry)row[i].get();
               out.row[i].append(new Entry(x.col, x.val));
               row[i].moveNext();
            }else if(M.row[i].index() != -1){
               Entry y = (Entry)M.row[i].get();
               out.row[i].append(new Entry(y.col, y.val));
               M.row[i].moveNext();
            }
         }
      }
      return out;
   }

   // sub()
   // subtracts this matrix from matrix M
   // pre: getSize() == M.getSize()
   Matrix sub(Matrix M){   
      if(getSize() != M.getSize()){
         throw new RuntimeException("Matrix Error: cannot add matrices of different sizes.");
      }

      Matrix out = new Matrix(getSize());
      if(this.equals(M)){
         out = new Matrix(getSize());
         return out;
      }
      for(int i=1; i<=getSize(); i++){
         row[i].moveFront();
         M.row[i].moveFront();
         while(row[i].index() != -1 || M.row[i].index() != -1){ 
            if(row[i].index() != -1 && M.row[i].index() != -1){ 
               Entry x = (Entry)row[i].get();
               Entry y = (Entry)M.row[i].get();
               if(x.col == y.col){ 
                  if(x.val - y.val == 0.0){
                     row[i].moveNext();
                     M.row[i].moveNext();
                  }else{
                     out.row[i].append(new Entry(x.col, x.val + (y.val*-1)));
                     row[i].moveNext();
                     M.row[i].moveNext();
                  }
               }else if(x.col > y.col){
                  out.row[i].append(new Entry(y.col, y.val*-1));
                  M.row[i].moveNext();
               }else if(x.col < y.col){
                  out.row[i].append(new Entry(x.col, x.val));
                  row[i].moveNext();
               }
            }else if(row[i].index() != -1){
               Entry x = (Entry)row[i].get();
               out.row[i].append(new Entry(x.col, x.val));
               row[i].moveNext();
            }else if(M.row[i].index() != -1){
               Entry y = (Entry)M.row[i].get();
               out.row[i].append(new Entry(y.col, y.val*-1));
               M.row[i].moveNext();
            }
         }
      }
      return out;
   }

   // transpose()
   // swaps the rows and columns of this matrix
   Matrix transpose(){
      Matrix out = new Matrix(getSize());
      for(int i=1; i<=getSize(); i++){
         row[i].moveFront();
         while(row[i].index() != -1){
            Entry current = (Entry)row[i].get();
            out.changeEntry(current.col, i, current.val);
            row[i].moveNext();
         }
      }
      return out;
   }

   // dot()
   // private helper function to compute the dot product of two lists
   private static double dot(List P, List Q){
      P.moveFront();
      Q.moveFront();
      double product = 0.0;
      while(P.index() != -1 && Q.index() != -1){
         Entry p = (Entry)P.get();
         Entry q = (Entry)Q.get();
         if(p.col == q.col){
            product += (p.val * q.val);
            P.moveNext();
            Q.moveNext();
         }else if(p.col < q.col){
            P.moveNext();
         }else if(p.col > q.col){
            Q.moveNext();
         }  
      }
      return product;
   }

   // mult()
   // multiplies two nxn matrices
   // pre: getSize() == M.getSize()
   Matrix mult(Matrix M){
      if(getSize() != M.getSize()){
         throw new RuntimeException("Matrix Error: cannot multiply matrices of different sizes");
      }

      Matrix out = new Matrix(getSize());
      Matrix T = M.transpose();
      for(int i=1; i<=getSize(); i++){
         if(row[i].length() == 0){
            continue;
         }
         for(int j=1; j<=getSize(); j++){
            if(T.row[j].length() == 0){
               continue;
            }
            out.changeEntry(i, j, dot(row[i], T.row[j]));
         }
      }
      return out;
   }

   // toString
   public String toString(){
      String out = "";
      for(int i = 1; i <= getSize(); ++i){
         if(row[i].length() > 0){
            out += (i + ": " + row[i] + "\n");
         }
      }
      return out;
   }
}

