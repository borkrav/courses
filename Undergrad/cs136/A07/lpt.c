#include "pointerplay.h"
#include <stdio.h>
#include <stdlib.h>

int l2(int n){
   
   if(n == 1){
      return 0;
   }
   
   else return 1 + l2(n/2);

}

int pow2 (int n){
   
   if (n==0){
      return 1;
   }
   
   else return 2 * pow2(n-1);


}

int lptsize(int n){

   return n - pow2(l2(n));

}

int main(){
   int aaa = 0;
   while(1 == scanf("%d", &aaa)){

   printf("%d\n", lptsize(aaa));

   }

   return 0;
}


