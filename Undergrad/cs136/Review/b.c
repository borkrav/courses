#include <stdio.h>
#include <string.h>


int main(){
   char c;
   while (1 == scanf(" %c", &c)){
      if (c > 96 && c < 123){
         printf("%c %d \n", c,  (c-96));
      }
   }
}
