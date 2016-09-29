#include "arraystuff.h"
#include <stdio.h>


int main(){
   int number=0;
   int size=0;
   int size2=0;
      
   printf("size of array 1: ");
   scanf(" %d", &size);
   int array[size];
   
   for(int i=0; i<size;i++){
      printf("%d: ",i);
      scanf(" %d", &number);
      array[i] = number;
   }
   
   printf("size of array 2: ");
   scanf(" %d", &size2);
   int array2[size2];
   
   for(int i=0; i<size2;i++){
      printf("%d: ",i);
      scanf(" %d", &number);
      array2[i] = number;
   }
   
   //printf("sum is %d\n", sumarray(array,size));
   //printf("max position is %d\n", maxarraypos (array,size));
   printf("result is: %d\n", lexlt(array, size, array2, size2));
}

   
