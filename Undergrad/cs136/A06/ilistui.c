#include <stdio.h>
#include "ilist_destructive.h"


void iprint(ilist list){
    ilist *printlist = &list;
    
    if(iempty_huh(*printlist) == 1){
    printf("empty list is empty\n");
    
    }    
    else{    
    while (iempty_huh(*printlist) != 1){
        
    printf("%d\n", ifirst(*printlist));
    ilist rest = irest(*printlist);
    printlist = &rest;
    }}
}


int main(){
    int number;

   /* while (1 == scanf("%d",&number)) {
           
       if (iempty_huh(list) == 1){
        list = icons_destroy(number, iempty());
        }
        
       else{
        ilist *prev = &list;
        list = icons_destroy(number, *prev);
       }
    }


    ilist x = icons_destroy(1, icons_destroy(6, iempty()));
    ilist y = icons_destroy(2, icons_destroy(5, iempty()));
    ilist b = icons_destroy(4, icons_destroy(10, iempty()));
    ilist z = iappend_destroy(x,y);
    ilist a = iappend_destroy(b,z);
    printlist(a);
    idelete(a);
  */
  
  
  //ilist a = icons_destroy(1, iempty());
  //ilist b = iappend_destroy(a, icopy(a));
  //ilist c = irest_destroy(b);
  ilist aaa = iempty();
  ilist bbb = icons_destroy(2, icons_destroy(3, icons_destroy(4, iempty())));

  ilist bb = iappend_destroy(bbb, aaa);
  bb = irest_destroy(bb);
  bb = iappend_destroy(bb, icons_destroy(5, iempty()));
  iprint(bb);
  printf("\n%d \n", ilength(bb));
  idelete(bb);

  
  

  

    
    
    
    
    }




