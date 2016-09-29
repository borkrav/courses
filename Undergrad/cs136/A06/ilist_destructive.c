#include <stdlib.h>
#include "ilist_destructive.h"

// The ilist ADT is a pointer to this secret struct
struct ilist_node {
   struct ilist_node *rest;
   char first;
   int length;
   ilist tail;
};

int counter=0;
ilist tail = NULL;


// icons creates a new node
ilist icons_destroy(char in, ilist il) {
  
  ilist result = malloc(sizeof(struct ilist_node));
  result->first = in;
  result->rest = il;
  counter+=1;
  result->length = counter;
  
  if(iempty_huh(il) == 1){
  tail = result;
  }
  
  result->tail = tail;
  return result;
}

// ifirst returns the first element of il
char ifirst(ilist il){
   return il->first;
}

// irest returns il with first element removed
ilist irest_destroy(ilist il){  
   ilist rest = il->rest;
   
   if(iempty_huh(rest) == 0){ 
      rest->length = il->length - 1;
      rest->tail = il->tail;
   }
   
   free(il);
   return rest;
}
ilist irest(ilist il){  //non destructive irest, for printing lists
   ilist rest = il->rest;
   return rest;
}

// ilist returns an empty ilist
// we have to use a function because struct ilist_node is secret
ilist iempty(){
   counter = 0; 
   return NULL;
}

// test for empty ilist
int iempty_huh(ilist il){
   return il == NULL;
}

// free memory for entire ilist
void idelete(ilist il){
   while (il != NULL) { 
      ilist next = il->rest;
      free(il);
      il = next;
   }
}

// computes the number of elements in il
int ilength(ilist il){ 

   if (iempty_huh(il) == 1){

     return 0; 
   }

   else{
     return il->length;
   }
}

ilist reverselist(ilist list){ //destructive
    ilist backlist = iempty();
    ilist revlist = list;
            
    while (iempty_huh(revlist) != 1){
      int number = ifirst(revlist);
       
      if (iempty_huh(backlist) == 1){
        backlist = icons_destroy(number, iempty());
        }
        
       else{
        ilist prev = backlist;
        backlist = icons_destroy(number, prev);
       } 
       
    revlist = irest_destroy(revlist);
    }   
   return backlist;

}

ilist icopy (ilist il){
   ilist result = iempty();
   ilist backlist = il;
   
   while (iempty_huh(backlist) != 1){
     ilist rest = result;
     result = icons_destroy(ifirst(backlist), rest);
     backlist = backlist->rest;
   }
   
   result = reverselist(result);

   return result;

}


ilist findtail(ilist list){ //non-destructive
return list->tail;
}

ilist iappend_destroy(ilist il1, ilist il2){
   
   if (iempty_huh(il1) == 1 && iempty_huh(il2) == 1){
   return iempty();
   }
   
   else if (iempty_huh(il1) == 1 && iempty_huh(il2) == 0){
   return il2;
   }
   
   else if (iempty_huh(il1) == 0 && iempty_huh(il2) == 1){
   return il1;
   }
   
   else{
     ilist tail = findtail(il1);
     tail->rest = il2;
     il1->tail = il2->tail;
     il1->length = ilength(il1)+ilength(il2);
     return il1; 
   }  
}







