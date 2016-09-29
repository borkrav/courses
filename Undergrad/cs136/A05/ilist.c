#include "ilist.h"
#include <stdlib.h>

// The ilist ADT is a pointer to this secret struct
struct ilist_node {
   struct ilist_node *rest;
   int first;
   int length;
};

int counter=0;



// icons creates a new node
ilist icons(int in, ilist il) {
   ilist r = malloc(sizeof(struct ilist_node));
   r->first = in;
   r->rest = il;
   counter+=1;
   r->length=counter;
   return r;
}

// ifirst returns the first element of il
int ifirst(ilist il){
   return il->first;
}

// irest returns il with first element removed
ilist irest(ilist il){
   return il->rest;
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

ilist reverselist(ilist list){
    ilist backlist = iempty();
    ilist *revlist = &list;
            
    while (iempty_huh(*revlist) != 1){
      int number = ifirst(*revlist);
       
      if (iempty_huh(backlist) == 1){
        backlist = icons(number, iempty());
        }
        
       else{
        ilist prev = backlist;
        backlist = icons(number, prev);
       } 
       
    ilist rest = irest(*revlist);
    revlist = &rest;
    }   
   return backlist;

}




ilist iappend(ilist il1, ilist il2){

    ilist result = iempty(); 

    ilist list1 = reverselist(il1);
    ilist list2 = reverselist(il2);

    ilist *buildlist1 = &list1;
    ilist *buildlist2 = &list2; 
 
   
   while(iempty_huh(*buildlist2) != 1){
  
      if (iempty_huh(result) == 1){
        result = icons(ifirst(*buildlist2), iempty());
      
      }
      
      else {
        ilist rest = result;
        result = icons(ifirst(*buildlist2),rest);
      
      }
      
      ilist rest = irest(*buildlist2);
      buildlist2 = &rest;
   }
   
   while(iempty_huh(*buildlist1) != 1){
   
   ilist next = result;
   result = icons(ifirst(*buildlist1), next);
   
   ilist rest = irest(*buildlist1);
   buildlist1 = &rest;  
   }
   
   idelete(list1);
   idelete(list2);
   return result;
}

