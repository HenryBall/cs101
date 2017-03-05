class ListTest{
   public static void main(String[] args){
      List A = new List();
      A.prepend(1);
      A.append(2);
      A.append(3);
      A.append(4);
      A.append(5);
      /*
      A.moveBack();
      System.out.println("The element at the last index is: " + A.get());
      System.out.println("The last index is: " + A.index());
      A.movePrev();
      System.out.println("The element of the second to last index is: " + A.get());
      A.insertBefore(99);
      A.movePrev();
      System.out.println(A.get());
      */
   }
}
