#include "ilist_destructive.h"
#include <stdio.h>

int main(){

   ilist line = iempty();
   char command = 0;
   char name = 0;
   
   while (1 == scanf(" %c", &command)){
  
      if(command == 'E'){
         scanf(" %c", &name);
         line = iappend_destroy(line, icons_destroy(name, iempty()));
         printf("seat %c\n", name);
      }
      
      else if (command == 'S'){
         
         if(iempty_huh(line) == 1){
            printf("serve ?\n");
         }
         
         else{
            printf("serve %c\n", ifirst(line));
            line = irest_destroy(line);
         }
     
      }
 
   }

   idelete(line);
}
