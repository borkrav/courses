#include <stdio.h>
#include "ilist.h"

int main(){
    int number;
    ilist list = iempty();
    while (1 == scanf("%d",&number)) {
           
       if (iempty_huh(list) == 1){
        list = icons(number, iempty());
        }
        
       else{
        ilist prev = list;
        list = icons(number, prev);
       }
    }
    
    ilist *printlist = &list;
        
    while (iempty_huh(*printlist) != 1){
        
    printf("%d\n", ifirst(*printlist));
    ilist rest = irest(*printlist);
    printlist = &rest;
    }
    idelete(list);
    
}

