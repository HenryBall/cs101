// Graph.c
// Henry Ball
// hfball
// pa4
// Graph ADT

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

// structs ----------------------

// private GraphObj type
typedef struct GraphObj{
   List *adj;
   int *color;
   int *parent;
   int *discover;
   int *finish;
   int order;
   int size;
}GraphObj;

// constructors-destructors------

// newGraph()
Graph newGraph(int n){
   Graph G = malloc(sizeof(GraphObj));
   G->adj = calloc(n+1, sizeof(List));
   G->color = calloc(n+1, sizeof(int)); // white:0, grey:1, black:2
   G->parent = calloc(n+1, sizeof(int));
   G->discover = calloc(n+1, sizeof(int));
   G->finish = calloc(n+1, sizeof(int));
   G->order = n; //num vericies
   G->size = 0; // num edges
   for(int i=1; i<=n; i++){
      G->adj[i] = newList();
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
      G->parent[i] = NIL;
      G->color[i] = -1;
   }
   return G;
}

// freeGraph()
void freeGraph(Graph *pG){
   Graph G = *pG;
   for (int i = 1; i <= G->order; i++){
      List L = G->adj[i];
      freeList(&L);
   }
   free(G->adj);
   free(G->color);
   free(G->parent);
   free(G->discover);
   free(G->finish);
   free(*pG);
   *pG = NULL;
}

// access functions--------------

// getOrder()
int getOrder(Graph G){
   if (G == NULL){
      printf("Graph Error: calling getOrder() on NULL Graph reference\n");
      exit(1);
   }

   return G->order;
}

// getSize()
int getSize(Graph G){
   if (G == NULL){
      printf("Graph Error: calling getSize() on NULL Graph reference\n");
      exit(1);
   }

   return G->size;
}

// getParent()
int getParent(Graph G, int u){
   if (G == NULL){
      printf("Graph Error: calling getParent() on NULL Graph reference\n");
      exit(1);
   }
   if (u < 1 || u > G->order){
      printf("Graph Error: calling getParent() with an out of bounds index\n");
      exit(1);
   }

   return G->parent[u];
}

// getSource()
int getDiscover(Graph G, int u){
   if (G == NULL){
      printf("Graph Error: calling getSource() on NULL Graph reference\n");
      exit(1);
   }

   return G->discover[u];
}

// getFinish
int getFinish(Graph G, int u){
   if (G == NULL){
      printf("Graph Error: calling getSource() on NULL Graph reference\n");
      exit(1);
   }

   return G->finish[u];
}

// manipulation procedures-------

// addEdge()
void addEdge(Graph G, int u, int v){
   if (G == NULL){
      printf("Graph Error: calling addEdge() on NULL Graph reference\n");
      exit(1);
   }
   if ((u < 1 || u > G->order) || (v < 1 || v > G->order)){
      printf("Graph Error: calling addEdge() with an out of order index\n");
      exit(1);
   }

   addArc(G, u, v);
   addArc(G, v, u);
   G->size--;
}

// addArc()
void addArc(Graph G, int u, int v){
   if (G == NULL){
      printf("Graph Error: calling addArc() on NULL Graph reference\n");
      exit(1);
   }
   if ((u < 1 || u > G->order) || (v < 1 || v > G->order)){
      printf("Graph Error: calling addArc() with an out of order index\n");
      exit(1);
   }

   moveFront(G->adj[u]);
   while (index(G->adj[u]) > -1){
      if (v < get(G->adj[u])){
         insertBefore(G->adj[u], v);
         return;
      }
      moveNext(G->adj[u]);
   }
   append(G->adj[u], v);
   G->size++;
}

// Visit()
void Visit(Graph G, List L, int x, int *time) {
   G->color[x] = 0;
   G->discover[x] = ++*time;
   moveFront(G->adj[x]);
   while (index(G->adj[x]) != -1){
      int y = get(G->adj[x]);
      if(G->color[y] == -1) {
         G->parent[y] = x;
         Visit(G, L, y, time);
                                                
      }
      moveNext(G->adj[x]);
                              
   }
   G->color[x] = 1;
   G->finish[x] = ++*time;
   prepend(L, x);
}

// DFS()
void DFS(Graph G, List S) {
   if(length(S) != getOrder(G)) {
      printf("Graph Error: calling DFS() without matching sizes\n");
      exit(1);                
   }

   for(int i = 1; i <= getOrder(G); ++i) {
      G->color[i] = -1;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
                                 
   }
   int time = 0;
   List L = newList();
   moveFront(S);
      while(index(S) >= 0) {
         int x = get(S);
         if(G->color[x] == -1) {
            prepend(S, x);
            Visit(G, L, x, &time);   
                                    
         }
         moveNext(S);                   
      }
      clear(S);
      moveFront(L);
      while (index(L) >= 0){
         append(S, get(L));
         moveNext(L);
      }
      freeList(&L);
}
// other ops---------------------

// transpose()
Graph transpose(Graph G){
   if (G == NULL){
      printf("Graph Error: calling transpose() on a NULL graph reference");
      exit(1);
   }

   Graph N = newGraph(G->order);
   for (int i = 1; i<=G->order; i++){
      moveFront(G->adj[i]);
      while (index(G->adj[i]) != -1){
         addArc(N, get(G->adj[i]), i);
         moveNext(G->adj[i]);
      }
   }
   return N;
}

// copyGraph()
Graph copyGraph(Graph G){
   if (G == NULL){
      printf("Graph Error: calling copyGraph() on a NULL graph reference\n");
      exit(1);
   }
   
   Graph N = newGraph(G->order);
   for (int i = 1; i<=N->order; i++){
      moveFront(G->adj[i]);
      while (index(G->adj[i]) >= 0){
         addArc(N, i, get(G->adj[i]));
         moveNext(G->adj[i]);
      }
      N->color[i] = G->color[i];
      N->parent[i] = G->parent[i];
      N->discover[i] = G->discover[i];
      N->finish[i] = G->finish[i];
   }
   N->order = G->order;
   N->size = G->size;
   return N;
}

// printGraph()
void printGraph(FILE *out, Graph G){
   if (G == NULL){
      printf("Graph Error: calling printGraph() on NULL graph reference\n");
      exit(1);
   }
   
   for (int i=1; i <= G->order; i++){
      fprintf (out, "%d: ", i);
      printList(out, G->adj[i]);
      fprintf(out, "\n");
   }
}
