// List.c
// Henry Ball
// hfball
// pa2
// Implementation file for the List ADT

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------
void deleteBack(List L);

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node back;
   Node front;
   Node cursor;
   int length;
   int cursorIndex;
}ListObj;

// constructors and destructors -----------------------------------------------

// private newNode() constructor
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// private freeNode() destructor
void freeNode(Node* pN){
   if(pN != NULL && *pN != NULL){
      free(*pN);
      *pN = NULL;
   }
}

// newList() constructor
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->cursorIndex = -1;
   return(L);
}

// freeList() destructor
void freeList(List* pL){
   if(pL != NULL && *pL != NULL){
      List L = *pL;
      while(length(L) != 0){
         deleteFront(L);
      }
      free(*pL);
      *pL = NULL;
   }
}

// access functions ------------------------------------------------------------

// length()
int length(List L){
   if(L == NULL){
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return(L->length);
}

// index()
int index(List L){
   if(L == NULL){
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   return(L->cursorIndex);
}

// front()
int front(List L){
   if(L == NULL){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if(length(L) == 0){
      printf("List Error: calling front() on an empty List reference\n");
      exit(1);
   }
   return(L->front->data);
}

// back()
int back(List L){
   if(L == NULL){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if(length(L) == 0){
      printf("List Error: calling back() on an empty List reference\n");
      exit(1);
   }
   return(L->back->data);
}

// get()
int get(List L){
   if(L == NULL){
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if(length(L) == 0){
      printf("List Error: calling get() on an empty List reference\n");
      exit(1);
   }
   if(index(L) < 0){
      printf("List Error: calling get get() on an undefined cursor\n");
      exit(1);
   }
   return(L->cursor->data);
}

// equals()
int equals(List A, List B){
   if(A == NULL || B == NULL){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1); 
   }
   int eq = 0;
   Node N = NULL;
   Node M = NULL;
   eq = (A->length == B->length);
   N = A->front;
   M = B->front;
   while(eq && N != NULL){
      eq = (N->data == M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

// manipulation procedures -----------------------------------------------------

// clear()
void clear(List L){
   if(L == NULL){
      printf("List Error: calling clear() on NULL list reference\n");
      exit(1);
   }

   while(length(L) != 0){
      deleteFront(L);
   }
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->cursorIndex = -1;
}

// moveFront()
void moveFront(List L){
   if(L == NULL){
      printf("List Error: calling moveFront() on NULL list reference\n");
      exit(1);
   }

   if(L->length != 0){
      L->cursor = L->front;
      L->cursorIndex = 0;
   }
}

// moveBack()
void moveBack(List L){
   if(L == NULL){
      printf("List Error: calling moveBack() on NULL list reference\n");
      exit(1);
   }

   if(L->length != 0){
      L->cursor = L->back;
      L->cursorIndex = L->length-1;
   }
}

// movePrev()
void movePrev(List L){
   if(L == NULL){
      printf("List Error: calling movePrev() on NULL list reference\n");
      exit(1);
   }

   if(L->cursorIndex >= 1){
      L->cursor = L->cursor->prev;
      L->cursorIndex--;
   }else if(L->cursorIndex == 0){
      L->cursor = NULL;
      L->cursorIndex = -1;
   }
}

// moveNext()
void moveNext(List L){
   if(L == NULL){
      printf("List Error: calling moveNext() on NULL list reference\n");
      exit(1);
   }

   if(L->cursorIndex >= 0 && L->cursorIndex != L->length-1){
      L->cursor = L->cursor->next;
      L->cursorIndex++;
   }else if(L->cursorIndex >= 0 && L->cursorIndex == L->length-1){
      L->cursor = NULL;
      L->cursorIndex = -1;
   }
}

// prepend()
void prepend(List L, int data){
   if(L == NULL){
      printf("List Error: calling prepend() on NULL list reference\n");
      exit(1);
   }

   Node N = newNode(data);
   if(L->length == 0){
      L->front = L->back = N;
   }else{
      N->next = L->front;
      L->front->prev = N;
      L->front = N;
      if(L->cursorIndex != -1 && L->cursor != NULL){
         L->cursorIndex++;
      }
   }
   L->length++;
}

// append()
void append(List L, int data){
   if(L == NULL){
      printf("List Error: calling append() on NULL list reference\n");
      exit(1);
   }

   Node N = newNode(data);
   if(L->length == 0){
      L->front = L->back = N;
   }else{
      N->prev = L->back;
      L->back->next = N;
      L->back = N;
   }
   L->length++;
}

// insertBefore()
void insertBefore(List L, int data){
   if(L == NULL){
      printf("List Error: calling insertBefore() on NULL list reference\n");
      exit(1);
   }
   if(L->length == 0){
      printf("List Error: trying to call insertBefore() on an empty list\n");
      exit(1);
   }
   if(L->cursorIndex == -1){
      printf("List Error: trying to call insertBefore() with an undefined cursor\n");
      exit(1);
   }

   if (index(L) == 0){
      prepend(L, data);
   }else{
      Node N = newNode(data);
      N->prev = L->cursor->prev;
      L->cursor->prev->next = N;
      N->next = L->cursor;
      L->cursor->prev = N;
      L->cursorIndex++;
      L->length++;
   }
}

// insertAfter()
void insertAfter(List L, int data){
   if(L == NULL){
      printf("List Error: calling insertAfter() on NULL list reference\n");
      exit(1);
   }
   if(L->length == 0){
      printf("List Error: trying to call insertAfter() on an empty list\n");
      exit(1);
   }
   if(L->cursorIndex == -1){
      printf("List Error: trying to call insertAfter() with an undefined cursor\n");
      exit(1);
   }

   if (index(L) == length(L)-1){
      append(L, data);
   }else{
      Node N = newNode(data);
      N->next = L->cursor->next;
      L->cursor->next->prev = N;
      N->prev = L->cursor;
      L->cursor->next = N;
      L->length++;
   }
}

// deleteFront()
void deleteFront(List L){
   if(L == NULL){
      printf("List Error: calling deleteFront() on NULL list reference\n");
      exit(1);
   }
   if(L->length == 0){
      printf("List Error: trying to call deleteFront() on an empty list\n");
      exit(1);
   }
   
   Node N = L->front;
   if(L->length > 1){
      if(L->front == L->cursor){
         L->cursor = NULL;
         L->cursorIndex = -1;
      }
      L->front = L->front->next;
   }else{
      L->front = L->back = L->cursor = NULL;
      L->cursorIndex = -1;
   }
   L->length--;
   freeNode(&N);
}

// deleteBack()
void deleteBack(List L){
   if(L == NULL){
      printf("List Error: calling deleteBack() on NULL list reference\n");
      exit(1);
   }
   if(L->length == 0){
      printf("List Error: trying to call deleteBack() on an empty list\n");
      exit(1);
   }
   
   Node N = L->back;
   if(L->length > 1){
      if(L->back == L->cursor){
         L->cursor = NULL;
         L->cursorIndex = -1;
      }
      L->back = L->back->prev;
   }else{
      L->front = L->back = L->cursor = NULL;
      L->cursorIndex = -1;
   }
   L->length--;
   freeNode(&N);
}

// delete()
void delete(List L){
   if(L == NULL){
      printf("List Error: calling delete() on NULL list reference\n");
      exit(1);
   }
   if(L->length == 0){
      printf("List Error: trying to call delete() on an empty list\n");
      exit(1);
   }
   if(L->cursorIndex == -1){
      printf("List Error: trying to call delete() with an undefined cursor\n");
      exit(1);
   }
   
   Node N = L->cursor;
   if(L->length > 1){
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
   }else{
      L->front = L->back = NULL;
   }
   L->cursor = NULL;
   L->cursorIndex = -1;
   L->length--;
   freeNode(&N);
}

// printList()
void printList(FILE* out, List L){
   if(L == NULL){
      printf("List Error: calling printList() on NULL list reference\n");
      exit(1);
   }

   Node N = NULL;
   for(N = L->front; N != NULL; N = N->next){
      fprintf(out, "%d ", N->data);
   }
}

// copyList()
List copyList(List L){
   List C = newList();
   Node N = L->front;

   while(N != NULL){
      append(C, N->data);
      N = N->next;
   }
   return C;
}
