// List.java
// Henry Ball
// hfball
// pa1
// This is a doubly linked list ADT

class List{
   // Private Node Class
   private class Node{
      int data;
      Node next;
      Node prev;

      Node(int data){
         this.data = data;
         next = null;
         prev = null;
      }

      public boolean equals(Object x){
         boolean eq = false;
         Node that;
         if (x instanceof Node){
            that = (Node) x;
            eq = (this.data==that.data);
         }
         return eq;
      }

      public String toString(){
         return String.valueOf(data);
      }
   }


   // List Fields 
   private Node front;
   private Node back;
   private Node cursor;
   private int length;
   private int cursorIndex;

   // Constructor 
   List(){
      front = back = cursor = null;
      length = 0;
      cursorIndex = -1;
   }

   // Access Functions
   int length(){
      return length;
   }

   int index(){
      return cursorIndex;
   }

   int front(){
      if(length > 0){
         return front.data;
      }else{
         throw new RuntimeException("front() error: Cannot return the front of an empty list");
      }
   }

   int back(){
      if(length > 0){
         return back.data;
      }else{
         throw new RuntimeException("back() error: cannot returnt he back of an empty list");
      }
   }

   int get(){
      if (length > 0 && cursor != null && cursorIndex >= 0){
         return cursor.data;
      }else{
         throw new RuntimeException("get() error: Cannot get an undefined cursor");
      }  
   }

   public boolean equals(List L){
      if (L.length() != length){
         return false;
      }

      L.moveFront();
      moveFront();
      while (L.index() != -1 && index() != -1){
         if (L.get() != get()){
            return false;
         }
         L.moveNext();
         moveNext();
      }
      return true;
   }

   // Manipulation Procedures 
   void clear(){
      front = back = cursor = null;
      length = 0;
      cursorIndex = -1;
   }

   void moveFront(){
      if (length != 0){
         cursor = front;
         cursorIndex = 0;
      }
   }

   void moveBack(){
      if (length != 0){
         cursor = back;
         cursorIndex = length - 1;
      }
   }

   void movePrev(){
      if (cursor != null && cursorIndex > 0){
         cursor = cursor.prev;
         cursorIndex--;
      }else{
         cursorIndex = -1;
         cursor = null;
      }
   }

   void moveNext(){
      if (cursor != null && cursorIndex != length-1){
         cursorIndex++;
         cursor = cursor.next;
      }else{
         cursorIndex = -1;
         cursor = null;
      }
   }

   void prepend(int data){
      Node N = new Node(data);
      if (length == 0){
         front = back = N;
      }else{
         N.next = front;
         front.prev = N;
         front = N;
         if(cursorIndex != -1 && cursor != null){
            cursorIndex++;
         }
      }
      length++;
   }

   void append(int data){
      Node N = new Node(data);
      if (length == 0){
         front = back = N;
      }else{
         back.next = N;
         N.prev = back;
         back = N;
      }
      length++;
   }

   void insertBefore(int data){
      Node N = new Node(data);
      if(length > 0 && cursorIndex >= 0){
         N.prev = cursor.prev;
         cursor.prev.next = N;
         N.next = cursor;
         cursor.prev = N;
         cursorIndex++;
         length++;
      }
   }

   void insertAfter(int data){
      Node N = new Node(data);
      if(length > 0 && cursorIndex >= 0){
         N.next = cursor.next;
         cursor.next.prev = N;
         N.prev = cursor;
         cursor.next = N;
         length++;
      }
   }

   void deleteFront(){
      if(length > 0){
         front = front.next;
         length--;
         if(cursorIndex > 0){
            cursorIndex--;
         }else{
            cursorIndex = -1;
            cursor = null;
         }
      }
   }

   void deleteBack(){
      if(length > 0){
         back = back.prev;
         length--;
         if(cursorIndex == length-1){
            cursor = null;
            cursorIndex = -1;
         }
      }
   }

   void delete(){
      if(length > 0 && cursorIndex >= 0){
         Node temp;
         temp = cursor.prev;
         temp.next = cursor.next;
         cursor = null;
         cursorIndex = -1;
         length--;
      }
   }
   
   //Other Methods
   public String toString(){
      StringBuffer sb = new StringBuffer();
      Node N = front;
      while(N!=null){
         sb.append(" ");
         sb.append(N.toString());
         N = N.next;
      }
      return new String(sb);
   }
}
