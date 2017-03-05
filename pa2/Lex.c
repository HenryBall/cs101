// Lex.c
// Henry Ball
// hfball
// pa2
// Sorts the lines in a file in lexicographic order using the List ADT

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 160

int main(int argc, char* argv[]){
   int count=0; 
   FILE *in, *out;
   char lines[MAX_LEN][MAX_LEN];
   List L = newList();

   if(argc != 3){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
   
   //open files for reading and writing
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if(in==NULL){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if(out==NULL){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   // read in lines from input file 
   while(fgets(lines[count], MAX_LEN, in) != NULL){
      count++;
   }
   
   // sort the lines array indirectly using the List ADT
   append(L, 0);
   for(int j=1; j<count; j++){
      moveFront(L);
      while(index(L) > -1 && strcmp(lines[j], lines[get(L)]) > 0){
         moveNext(L);
      }
      if(index(L) == -1){
         append(L, j);
      }else if(index(L) == 0){
         prepend(L, j);
      }else{
         insertBefore(L, j);
      }
   }
   
   // print to the output file
   for(moveFront(L); index(L)>=0; moveNext(L)){
      fprintf(out, "%s", lines[get(L)]);
   }

   freeList(&L);
   fclose(in);
   fclose(out);
   return(0);
}

