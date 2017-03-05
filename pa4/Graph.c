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
   int *distance;
   int order;
   int size;
   int source;
}GraphObj;

// constructors-destructors------

// newGraph()
Graph newGraph(int n){
   Graph G = malloc(sizeof(GraphObj));
   G->adj = calloc(n+1, sizeof(List));
   G->color = calloc(n+1, sizeof(int)); // white:0, grey:1, black:2
   G->parent = calloc(n+1, sizeof(int));
   G->distance = calloc(n+1, sizeof(int));
   G->order = n; //num vericies
   G->size = 0; // num edges
   G->source = NIL;
   for(int i=1; i<=n; i++){
      G->adj[i] = newList();
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
   free(G->distance);
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

// getSource()
int getSource(Graph G){
   if (G == NULL){
      printf("Graph Error: calling getSource() on NULL Graph reference\n");
      exit(1);
   }

   if (G->source == NIL){
      return NIL;
   }else{
      return G->source;
   }
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

   if (G->source == NIL){
      return NIL;
   }else{
      return G->parent[u];
   }
}

// getDist()
int getDist(Graph G, int u){
   if (G == NULL){
      printf("Graph Error: calling getDist() on NULL Graph reference\n");
      exit(1);
   }
   if (u < 1 || u > G->order){
      printf("Graph Error: calling getDist() with an out of bounds index\n");
      exit(1);
   }

   if (G->source == NIL){
      return INF;
   }else{
      return G->distance[u];
   }
}

// getPath()
void getPath(List L, Graph G, int u){
   if (G == NULL){
      printf("Graph Error: calling getPath() on NULL Graph reference\n");
      exit(1);
   }
   if (u < 1 || u > G->order){
      printf("Graph Error: calling getPath() with an out of bounds index\n");
      exit(1);
   }
   if (G->source == NIL){
      printf("Graph Error: calling getPath() without a defined source\n");
      exit(1);
   }

   int x = G->source;
   if(u == x){
      prepend(L, x);
   }else if(G->parent[u] == NIL){
      append(L, NIL);
   }else{
      prepend(L, u);
      getPath(L, G, G->parent[u]);
   }
}

// manipulation procedures-------

// makeNull()
void makeNull(Graph G){
   if (G == NULL){
      printf("Graph Error: calling makeNull() on NULL Graph reference\n");
      exit(1);
   }

   for (int i=1; i <= G->order; i++){
      clear(G->adj[i]);
   } 
}

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

// BFS()
void BFS(Graph G, int s){
   for (int i=1; i < (getOrder(G) + 1); i++){
      G->color[i] = 0;
      G->parent[i] = NIL;
      G->distance[i] = INF;
   }
   G->source = s;
   G->color[s] = 1;
   G->parent[s] = NIL;
   G->distance[s] = 0;
   List Q = newList();
   append(Q, s);
   while(length(Q) != 0){
      int x = front(Q);
      deleteFront(Q);
      List adj = G->adj[x];
      moveFront(adj);
      while(index(adj) != -1){
         int y = get(adj);
         if(G->color[y] == 0){
            G->color[y] = 1;
            G->parent[y] = x;
            G->distance[y] = G->distance[x] + 1;
            append(Q, y);
         }
         moveNext(adj);
      }
      G->color[x] = 2;
   }
   freeList(&Q);
}

// other ops---------------------

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
