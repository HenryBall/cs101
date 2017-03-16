// FindPath.c
// Henry Ball
// hfball
// 3-1-17
// prints the adjacency lists and specified distances from the graph given in
// the input file

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Graph.h"

#define MAX_LEN 160

int main(int argc, char *argv[]){
   FILE *in, *out;
   int size, n, m;
   char line[MAX_LEN];
   char* token;
   
   // check for usae errors
   if (argc != 3){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
   
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   
   if (in == NULL){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if (out == NULL){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   
   // read in graph size
   fgets(line, MAX_LEN, in);
   size = strtol(line, NULL, 10);
   Graph G = newGraph(size);
   
   // read in and print adjacency list
   fgets(line, MAX_LEN, in);
   while(strcmp(line, "0 0\n") != 0){
      token = strtok(line, " \n");
      n = strtol(token, NULL, 10);
      token = strtok(NULL, " /n");
      m = strtol(token, NULL, 10);
      addArc(G, n, m);
      fgets(line, MAX_LEN, in);
   }
   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out, G);
   fprintf(out, "\n");
   
   // run DFS on G and the transpose of G
   List S = newList();
   for (int i = 1; i<=size; i++) append(S, i);
   DFS(G, S);
   Graph T = transpose(G);
   DFS(T, S);
   
   // calculate num of scc's
   int comp = 0;
   moveBack(S);
   while (index(S) != -1){
      if (getParent(T, get(S)) == NIL){
         comp++;
      }
      movePrev(S);
   }
   
   // use list S to print the scc's
   List scc = newList();
   moveBack(S);
   int i = 1;
   fprintf(out, "G contains %d strongly connected components: \n", comp);
   while (index(S) != -1 && i<=comp){
      fprintf(out, "Component %d: ", i);
      while (getParent(T, get(S)) != NIL){
         prepend(scc, get(S));
         movePrev(S);
      }
      prepend(scc, get(S));
      printList(out, scc);
      clear(scc);
      movePrev(S);
      fprintf(out, "\n");
      i++;
   }
   
   // free mem
   freeGraph(&G);
   freeGraph(&T);
   freeList(&S);
   freeList(&scc);
   // close files
   fclose(in);
   fclose(out);
   return(0);
}
