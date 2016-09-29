#include <stdio.h>
#include "ilist.h"

int main(){
    int number;
    ilist list = iempty();
    ilist list2 = iempty();
    while (1 == scanf("%d",&number)) {
           
       if (iempty_huh(list) == 1){
        list = icons(number, iempty());
        }
        
       else{
        ilist prev = list;
        list = icons(number, prev);
       }
    }
      
   
    ilist *revlist = &list;
        
    while (iempty_huh(*revlist) != 1){
      
      int number = ifirst(*revlist);
       
      if (iempty_huh(list2) == 1){
        list2 = icons(number, iempty());
        }
        
       else{
        ilist prev = list2;
        list2 = icons(number, prev);
       } 
 
    ilist rest = irest(*revlist);
    revlist = &rest;
    }
    
    idelete(list);
    
    ilist *printlist = &list2;
    int length=0;  
    while (iempty_huh(*printlist) != 1){
    ilist rest = irest(*printlist);
    printlist = &rest;
    length+=1;
    }  
    
    printf("%d\n", length); 
    printlist = &list2;    
    while (iempty_huh(*printlist) != 1){
        
    printf("%d\n", ifirst(*printlist));
    ilist rest = irest(*printlist);
    printlist = &rest;
    }
    
    idelete(list2);
    
}

