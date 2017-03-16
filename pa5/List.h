// List.h
// Henry Ball
// hfball
// pa2
// Header file for the list ADT

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// exported type --------------------------------------------------------------
typedef struct ListObj* List;

// constructors and destructors -----------------------------------------------

// newList()
List newList(void);

// freeList()
void freeList(List* pL);

// access functions -----------------------------------------------------------

// length()
int length(List L);

// index()
int index(List L);

// front()
int front(List L);

// back()
int back(List L);

// get()
int get(List L);

// equals()
int equals(List A, List B);

// manipulation procedures ----------------------------------------------------

// clear()
void clear(List L);

// moveFront()
void moveFront(List L);

// moveBack()
void moveBack(List L);

//movePrev()
void movePrev(List L);

//moveNext()
void moveNext();

// prepend()
void prepend(List L, int data);

// append()
void append(List L, int data);

// insertBefore()
void insertBefore(List L, int data);

// insertAfter()
void insertAfter(List L, int data);

// deleteFront()
void deleteFront(List L);

// deleteBack()
void deleteFront(List L);

// delete()
void delete(List L);

// other operations ------------------------------------------------------------

// printList()
void printList(FILE* out, List L);

// copyList(List L)
List copyList(List L);

#endif 
