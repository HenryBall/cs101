// ListTest.java
// Henry Ball
// hfball
// pa3
// test file for the List ADT

public class ListTest{
   public static void main (String[] args){
      List L = new List();
      L.append(1);
      L.append(3);
      L.prepend(0);
      L.moveFront();
      L.moveNext();
      L.moveNext();
      L.insertBefore(2);
      System.out.println(L);
      L.delete();
      System.out.println(L);
      L.moveFront();
      System.out.println(" " + L.index());
      L.moveNext();
      System.out.println(" " + L.get());
      L.insertAfter(7);
      L.moveBack();
      L.get();
      List A = new List();
      A.prepend(9);
      System.out.println(A.equals(L));
      L.clear();
      System.out.println(L);
   }
}
