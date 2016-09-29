#include <stdio.h>


int main(){

   int number = 0;
   int sum=0;
   
   while(1 == scanf(" %d", &number)){
  
      sum = number + sum;
   }
   
   printf("The sum is %d\n", sum);
   return 0;

}
