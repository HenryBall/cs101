// MatrixTest.java
// Henry Ball
// hfball
// pa3
// test file for Matrix.java

public class MatrixTest{
   public static void main(String[] args){
      int n = 1000;
      Matrix A = new Matrix(n);
      Matrix B = new Matrix(n);
      
      A.changeEntry(1, 2, 10);
      A.changeEntry(2, 1, 50);
      A.changeEntry(3, 2, 3);
      A.changeEntry(3, 1, 4);
      A.changeEntry(1, 3, 7);
      A.changeEntry(3, 3, 67);

      B.changeEntry(1, 1, 11);
      B.changeEntry(1, 2, 3);
      B.changeEntry(1, 3, 5);
      B.changeEntry(2, 1, 6);
      B.changeEntry(2, 3, 90);
      B.changeEntry(3, 1, 7);

      System.out.println("A has " + A.getNNZ() + " non-zero elements");
      System.out.println(A);

      System.out.println("B has " + B.getNNZ() + " non-zero elements");
      System.out.println(B);

      System.out.println("A * 5");
      System.out.println(A.scalarMult(5));

      System.out.println("A + B");
      System.out.println(A.add(B));

      System.out.println("A - B");
      System.out.println(A.sub(B));

      System.out.println("A * B");
      System.out.println(A.mult(B));

      System.out.println("Copy of A");
      Matrix M = A.copy();
      System.out.println(M);
      System.out.println(M.equals(A));

      M.makeZero();
      System.out.println(M);
      System.out.println(M.equals(A));

   }
}
