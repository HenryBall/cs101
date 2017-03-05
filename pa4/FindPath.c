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
#include "List.h"

#define MAX_LEN 160

int main(int argc, char *argv[]){
   int n, m;
   FILE *in, *out;
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
   n = strtol(line, NULL, 10);
   Graph G = newGraph(n);

   // read in and print adjacency list
   fgets(line, MAX_LEN, in);
   while(strcmp(line, "0 0\n") != 0){
      token = strtok(line, " \n");
      n = strtol(token, NULL, 10);
      token = strtok(NULL, " /n");
      m = strtol(token, NULL, 10);
      addEdge(G, n, m);
      fgets(line, MAX_LEN, in);
   }
   printGraph(out, G);
   fprintf(out, "\n");

   // read in and print specified distances
   fgets(line, MAX_LEN, in);
   while(strcmp(line, "0 0\n") != 0){
      token = strtok(line, " \n");
      n = strtol(token, NULL, 10);
      token = strtok(NULL, " /n");
      m = strtol(token, NULL, 10);
      List L = newList();
      BFS(G, n);
      int d = getDist(G, m);
      fprintf(out, "The distance from %d to %d is ", n, m);
      if (d == -1){
         fprintf(out, "Infinity\n");
         fprintf(out, "No such %d-%d path exists\n", n, m);
      }else{
         fprintf(out, "%d\n", d);
         fprintf(out, "The shortest %d-%d path is: ", n, m);
         getPath(L, G, m);
         printList(out, L);
         fprintf(out, "\n");
      }
      fprintf(out, "\n");
      fgets(line, MAX_LEN, in);
      freeList(&L);
   }
   freeGraph(&G);

   // close files
   fclose(in);
   fclose(out);

}
