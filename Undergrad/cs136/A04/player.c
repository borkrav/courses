#include <stdio.h>
#include "newgame.h"
#include "playnewgame.h"

int main(){
   int gamesize;
   printf("What size game?\n");
   while (1 == scanf("%d",&gamesize)) {
      printf("Game size %d finished in %d moves\n",gamesize,playgame(gamesize));
      printf("New game size? Control-D (EOF) to quit\n");
   }
   return 0;
}
//214748367
