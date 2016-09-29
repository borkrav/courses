#include <stdio.h>
#include "ilist.h"

static void iprint(char *label, ilist d){
   printf("%s ",label);
   while (!iempty_huh(d)) {
      printf(" %d",ifirst(d));
      d = irest(d);
   }
   printf("\n");
}

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
    
    printf("%d\n", ilength);
    idelete(list);
    
    }
