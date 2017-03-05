// Henry Ball
// GraphTest.c
// hfball
// 3-1-17
// test file for Graph.c

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]){
   Graph G = newGraph(20);
   addEdge(G, 1, 2);
   addEdge(G, 2, 5);
   addEdge(G, 3, 8);
   addEdge(G, 3, 7);
   addArc(G, 10, 20);
   addArc(G, 20, 10);
   int j = 1;
   for (int i=10; i<=20; i++){
      addEdge(G, i, j);
      j++;
   }
   printGraph(stdout, G);
   BFS(G, 10);
   printf("Order: %d\n", getOrder(G));
   printf("Size: %d\n", getSize(G));
   printf("Source: %d\n", getSource(G));
   printf("Parent: %d\n", getParent(G, 2));
   printf("Distance: %d\n", getDist(G, 11));
   List L = newList();
   getPath(L, G, 2);
   printList(stdout, L);
   printf("\n");
   makeNull(G);
   printf("\n");
   printGraph(stdout, G);
}
