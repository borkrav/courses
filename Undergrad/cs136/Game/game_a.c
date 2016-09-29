#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <unistd.h> //temporary unix libraries for the sleep command
//#include <windows.h> uncomment if running on windows

char board[25][25];  //a two dimensional array of charecter values
int height;
int width;
int score = 0;
FILE *output;

//a function that will seed the random board generator
void sRand()
{
   time_t timer = 0;
   time(&timer);   
   srand(timer);
}

//a function used to calculate powers of 2 recursively
int power2 (int a){
   if (a==0){
      return 1;
   } 
   else return 2 * power2(a-1);
}


int aicrawlan(int x, int y){
   
   int aiboard[width][height];
   
   for (int xi = 0; xi < width; xi++){
      for (int yi = 0; yi < height; yi++){
         aiboard[xi][yi] = board[xi][yi];
      }
   }
   
   
   /* BEGIN OF UPWARD SCORE CRAWLER */
   //check if we've crawled UP into edge of the aiboard
   if ((aiboard[x][y] == 117) && (y == 0)){
      
      if (aiboard[x][height-1] == 117){
         aiboard[x][y] = 32;
         return 1 + aicrawlan(x, height-1);
      }
       else {
         aiboard[x][y] = 32;
         return 1;
      }
   
   } else if (aiboard[x][y] == 117 && (aiboard[x][y-1] == 120 && aiboard[x-1][y-1] != 120)) { //hit a Bottom-left diamond
      // if the diamond carries the annhilate
      if (aiboard[x-1][y-1] == 108){
         aiboard[x][y] = 32;
         return 1 + aicrawlan(x-1,y-1);
      } else {
         aiboard[x][y] = 32;
         return 1;
      }
   
   } else if (aiboard[x][y] == 117 && (aiboard[x][y-1] == 120 && aiboard[x+1][y-1] != 120)){ // hit a bottom-right diamond
   
      if (aiboard[x+1][y-1] == 114){
         aiboard[x][y] = 32;
         return 1 + aicrawlan(x+1,y-1);
      } else {
         aiboard[x][y] = 32;
         return 1;
      }
   
   } else if (aiboard[x][y] == 117 && aiboard[x][y-1] == 117){
      aiboard[x][y] = 32;
      return 1 + aicrawlan(x, y-1);
   
   } else if (aiboard[x][y] == 117 && aiboard[x][y-1] != 117){
   aiboard[x][y] = 32;
   return 1;
   } /* END OF UPWARD SCORE CRAWLER */
   /* BEGINNING OF LEFTWARD SCORE CRAWLER */
   else if (aiboard[x][y] == 108 && x == 0){
      //check to see if we hit the left edge of the aiboard
      
      if (aiboard[width-1][y] == 108){ 
         aiboard[x][y] = 32;
         return 1 + aicrawlan(width-1, y); 
      } else {
         aiboard[x][y] = 32;
         return 1;
      }
      // now check to see if we hit a bottom-right diamond
   } else if (aiboard[x][y] == 108 && (aiboard[x-1][y] == 120 && aiboard[x-1][y+1] != 120)){
      if (aiboard[x-1][y+1] == 100){
         aiboard[x][y] = 32;
         return 1 + aicrawlan(x-1, y+1);
      } else {
         aiboard[x][y] = 32;
         return 1;
      }   
   
   //now check to see if we hit a top-right diamond
   } else if (aiboard[x][y] == 108 && (aiboard[x-1][y] == 120 && aiboard[x-1][y-1] != 120)){
   
      if (aiboard[x-1][y-1] == 117){
         aiboard[x][y] = 32;
         return 1 + aicrawlan(x-1,y-1);
      } else {
         aiboard[x][y] = 32;
         return 1;
      }
   
   } else if (aiboard[x][y] == 108 && aiboard[x-1][y] == 108){
      aiboard[x][y] = 32;
      return 1 + aicrawlan(x-1, y);
   } else if (aiboard[x][y] == 108 && aiboard[x-1][y] != 108){
      aiboard[x][y] = 32;
      return 1;
   } /* END LEFT CRAWLING BLOCK*/
     /* BEGIN DOWN-CRAWLING BLOCK */
   else if (aiboard[x][y] == 100 && y == height-1){ //check to see if we hit the bottom edge of the aiboard
      
      if (aiboard[x][0] == 100){
         aiboard[x][y] = 32;
         return 1 + aicrawlan(x,0);
      } else {
         aiboard[x][y] = 32;
         return 1;
      }
      
   } else if (aiboard[x][y] == 100 && (aiboard[x][y+1] == 120 && aiboard[x-1][y+1] != 120)){ //top-left diamond
   
      if (aiboard[x-1][y+1] == 108){
         aiboard[x][y] = 32;
         return 1 + aicrawlan(x-1,y+1);
      } else {
         aiboard[x][y] = 32;
         return 1;
      }
   
   } else if (aiboard[x][y] == 100 && (aiboard[x][y+1] == 120 && aiboard[x+1][y+1] != 120)){ //top-right diamond
   
      if (aiboard[x+1][y+1] == 114){
         aiboard[x][y] = 32;
         return 1 + aicrawlan(x+1, y+1);
      } else {
         aiboard[x][y] = 32;
         return 1;
      }
   
   } else if (aiboard[x][y] == 100 && aiboard[x][y+1] == 100){
      aiboard[x][y] = 32;
      return 1 + aicrawlan(x, y+1);
   } else if (aiboard[x][y] == 100 && aiboard[x][y+1] != 100){
      aiboard[x][y] = 32;
      return 1;
      /* END DOWN CRAWLING BLOCK */
      /* BEGIN RIGHT-CRAWLING BLOCK */
   } else if (aiboard[x][y] == 114 && x == width-1){ //check to see if we hit the edge of the aiboard
      if (aiboard[0][y] == 114){
         aiboard[x][y] = 32;
         return 1 + aicrawlan (0,y);
      } else {
         aiboard[x][y] = 32;
         return 1;
      }
   } else if (aiboard[x][y] == 114 && (aiboard[x+1][y] == 120 && aiboard[x+1][y-1] != 120)){ //hit top-left diamond
   
      if (aiboard[x+1][y-1] == 117){
            aiboard[x][y] = 32;
            return 1 + aicrawlan(x+1, y-1);
         } else {
            aiboard[x][y] = 32;
            return 1;
         }
   
   } else if (aiboard[x][y] == 114 && (aiboard[x+1][y] == 120 && aiboard[x+1][y+1] != 120)){ //hit bottom-left diamond
   
      if (aiboard[x+1][y+1] == 100) {
         aiboard[x][y] = 32;
         return 1 + aicrawlan(x+1,y+1);
      } else {
         aiboard[x][y] = 32;
         return 1;
      }
   
   } else if (aiboard[x][y] == 114 && aiboard[x+1][y] == 114){
      aiboard[x][y] = 32;
      return 1 + aicrawlan(x+1, y);
   } else if (aiboard[x][y] == 114 && aiboard[x+1][y] != 114){
      aiboard[x][y] = 32;
      return 1;
   }
}

int aiplaygame(int x, int y){

   int pointeeX, pointeeY;
   int movescore = 0;
   
      int aiboard[width][height];
   
   for (int xi = 0; xi < width; xi++){
      for (int yi = 0; yi < height; yi++){
         aiboard[xi][yi] = board[xi][yi];
      }
   }
   
   if (aiboard[x][y] == 117){ // pointing up
      /* BEGIN UPWARD MOVEMENTS */
      if ( y == 0 ){
         //pointing at the top of the aiboard
         pointeeX = x;
         pointeeY = height-1;

      } else if ((aiboard[x][y-1] == 120) && (aiboard[x+1][y-1] != 120)){
         //pointing at bottom-right diamond
         pointeeX = x+1;
         pointeeY = y-1;
         //check to see if this will be a slide through a diamond
         if (aiboard[pointeeX][pointeeY] == 32){
            aiboard[x][y] = 32;
            aiboard[pointeeX][pointeeY] = 114;
            return -1;
         } else if (aiboard[pointeeX][pointeeY] == 114){ // check if we annhilate through the diamond
            return power2(aicrawlan(x, y));
         } else if (aiboard[x][y] == aiboard[pointeeX][pointeeY]) {
            aiboard[pointeeX][pointeeY] = 100; // don't get confused and annhilate same direction thru diamond
            return -1;
         }
         
      }  else if ((aiboard[x][y-1] == 120) && (aiboard[x-1][y-1] != 120)){
         //pointing at bottom-left diamond
         pointeeX = x-1;
         pointeeY = y-1;
         //check to see if this will be a slide through a diamond
         if (aiboard[pointeeX][pointeeY] == 32){
            aiboard[x][y] = 32;
            aiboard[pointeeX][pointeeY] = 108;
            return -1;
         } else if (aiboard[pointeeX][pointeeY] == 108) { 
         //check if we annhilate through the diamond
            return power2(aicrawlan(x, y));
         
         } else if (aiboard[x][y] == aiboard[pointeeX][pointeeY]){
            aiboard[pointeeX][pointeeY] = 100; // don't get confused and annhilate same direction thru diamond
            return -1;
         }
      } else {
         pointeeX = x;
         pointeeY = y-1;
      }
      
      if (aiboard[x][y] == aiboard[pointeeX][pointeeY]){ // check to see if we have an annhilate
         return power2(aicrawlan(x,y));
      } else if (aiboard[pointeeX][pointeeY] == 32){ //check if we are pointing at an empty space
         aiboard[pointeeX][pointeeY] = aiboard[x][y];
         aiboard[x][y] = 32;
         return -1;
      } 
      
      /* END UPWARD MOVEMENTS */  
      }      
      
      
    else if (aiboard[x][y] == 100){ //pointing down
   /* BEGIN DOWNARD MOVEMENTS */
   
      if (y == height-1){ //check to see if we are at edge of the aiboard
         pointeeX = x;
         pointeeY = 0;
      } else if (aiboard[x][y-1] == 120 && aiboard[x-1][y+1] != 120){
      // top-left diamond tile
         pointeeX = x-1;
         pointeeY = y+1;
         
         // check to see if this will be a diamond slide
         if (aiboard[pointeeX][pointeeY] == 32){
            aiboard[x][y] = 32;
            aiboard[pointeeX][pointeeY] = 108;
            return -1;
         } else if (aiboard[pointeeX][pointeeY] == 108){ //check for annhilate thru diamond
            return power2(aicrawlan(x,y));         
         } else if (aiboard[pointeeX][pointeeY] == aiboard[x][y]){ // flip thru diamond
            aiboard[pointeeX][pointeeY] = 117;
            return -1;
         }
      } 
      
      else if (aiboard[x][y-1] == 120 && aiboard[x+1][y+1] != 120) {
      // top-right diamond
         pointeeX = x+1;
         pointeeY = y+1;
         
         //check to see if this will be a diamond slide
         if (aiboard[pointeeX][pointeeY] == 32){
            aiboard[x][y] = 32;
            aiboard[pointeeX][pointeeY] = 114;
            return -1;
         } else if (aiboard[pointeeX][pointeeY] == 114){ // diamond annhilate
            return power2(aicrawlan(x,y));
         } else if (aiboard[x][y] == aiboard[pointeeX][pointeeY]){ // diamond flip
            aiboard[pointeeX][pointeeY] = 117;
            return -1;
         }
         
         
      } else {
         pointeeX = x;
         pointeeY = y+1;
      }
      
      if (aiboard[x][y] == aiboard[pointeeX][pointeeY]){
         return power2(aicrawlan(x,y));
      } else if (aiboard[pointeeX][pointeeY] == 32){
         aiboard[pointeeX][pointeeY] = aiboard[x][y];
         aiboard[x][y] = 32;
         return -1;
      }
      
      // END DOWNWARD MOVEMENTS
      
   } else if (aiboard[x][y] == 108){ //pointing left
      // BEGIN LEFTWARD MOVEMENTS


      if (x == 0){
         // check to see if we've hit the left-edge of the aiboard
         pointeeX = width-1;
         pointeeY = y;
      } else if (aiboard[x-1][y] == 120 && aiboard[x-1][y-1] != 120){
         // check for top-right diamond
         pointeeX = x-1;
         pointeeY = y-1;
         
         //check if this is a diamond slide
         if (aiboard[pointeeX][pointeeY] == 32){
            aiboard[x][y] = 32;
            aiboard[pointeeX][pointeeY] = 117;
            return -1;         
         }  else if (aiboard[pointeeX][pointeeY] == 117){ //anhilate thru diamond
            return power2(aicrawlan(x,y));
         } else if (aiboard[pointeeX][pointeeY] == aiboard[x][y]){ //flip thru diamond
            aiboard[pointeeX][pointeeY] = 114;
            return -1;
         }
                         
      } else if (aiboard[x-1][y] == 120 && aiboard[x-1][y+1] != 120){
         //bottom-right diamond
         pointeeX = x-1;
         pointeeY = y+1;
         
         // check if this is a diamond slide
         if (aiboard[pointeeX][pointeeY] == 32){
            aiboard[x][y] = 32;
            aiboard[pointeeX][pointeeY] = 100;
            return -1;
         } else if (aiboard[pointeeX][pointeeY] == 100){
            return power2(aicrawlan(x,y)); //annhilate thru diamond
         } else if (aiboard[pointeeX][pointeeY] == aiboard[x][y]){
            aiboard[pointeeX][pointeeY] = 114; // flip thru diamond
            return -1;
         }
      
      } else {
         pointeeX = x-1;
         pointeeY = y;
      }

      if (aiboard[x][y] == aiboard[pointeeX][pointeeY]){
         return power2(aicrawlan(x,y));
      } else if (aiboard[pointeeX][pointeeY] == 32){
         aiboard[pointeeX][pointeeY] = aiboard[x][y];
         aiboard[x][y] = 32;
         return -1;
      
      }

   /* END LEFTWARD MOVEMENT */

   } else if (aiboard[x][y] == 114){ //pointing right
     // BEGIN RIGHT-WARD MOVEMENT 
      if (x == width-1){
         // check to see if we hit the edge of the aiboard
         pointeeX = 0;
         pointeeY = y;
      } else if (aiboard[x+1][y] == 120 && aiboard[x+1][y-1] != 120){
         // top-left diamond
         pointeeX = x+1;
         pointeeY = y-1;
         
         // check for a dimaond-slide
         if (aiboard[pointeeX][pointeeY] == 32){
            aiboard[x][y] = 32;
            aiboard[pointeeX][pointeeY] = 117;
            return -1;
         } else if (aiboard[pointeeX][pointeeY] == 117){
            return power2(aicrawlan(x,y)); //diamond annhilate
         } else if (aiboard[x][y] == aiboard[pointeeX][pointeeY]){
            aiboard[pointeeX][pointeeY] = 108; // diamond flip
            return -1;
         }
      
      } else if (aiboard[x+1][y] == 120 && aiboard[x+1][y+1] != 120){
         //check for bottom-left diamond
         pointeeX = x+1;
         pointeeY = y+1;
         
         // check for a diamond-slide
         if (aiboard[pointeeX][pointeeY] == 32){
            aiboard[x][y] = 32;
            aiboard[pointeeX][pointeeY] = 100;
            return -1;
         } else if (aiboard[pointeeX][pointeeY] == 100){
            return power2(aicrawlan(x,y)); //anhilate thru diamond
         } else if (aiboard[x][y] == aiboard[pointeeX][pointeeY]){
            aiboard[pointeeX][pointeeY] = 117;
            return -1;
         }
      
      } else {
         pointeeX = x+1;
         pointeeY = y;
      
      }
      
      if (aiboard[x][y] == aiboard[pointeeX][pointeeY]){
         return power2(aicrawlan(x,y));
      } else if (aiboard[pointeeX][pointeeY] == 32){
         aiboard[pointeeX][pointeeY] = aiboard[x][y];
         aiboard[x][y] = 32;
         return -1;
      }
      
     
   } else if (aiboard[x][y] == 120) {
      return 0;
   } else if (aiboard[x][y] == 32){
      return 0;
   }
   
   // if we make it thus far, just flip the pointee
   if (aiboard[pointeeX][pointeeY] == 100){
      aiboard[pointeeX][pointeeY] = 117;
      return -1;
   } else if (aiboard[pointeeX][pointeeY] == 108) {
      aiboard[pointeeX][pointeeY] = 114;
      return -1;
   } else if (aiboard[pointeeX][pointeeY] == 114) {
      aiboard[pointeeX][pointeeY] = 108;
      return -1;
   } else if (aiboard[pointeeX][pointeeY] == 117){
      aiboard[pointeeX][pointeeY] = 100;
      return -1;
   }
   
   

}


int crawlan(int x, int y){
   
   /* BEGIN OF UPWARD SCORE CRAWLER */
   //check if we've crawled UP into edge of the board
   if ((board[x][y] == 117) && (y == 0)){
      
      if (board[x][height-1] == 117){
         board[x][y] = 32;
         return 1 + crawlan(x, height-1);
      }
       else {
         board[x][y] = 32;
         return 1;
      }
   
   } else if (board[x][y] == 117 && (board[x][y-1] == 120 && board[x-1][y-1] != 120)) { //hit a Bottom-left diamond
      // if the diamond carries the annhilate
      if (board[x-1][y-1] == 108){
         board[x][y] = 32;
         return 1 + crawlan(x-1,y-1);
      } else {
         board[x][y] = 32;
         return 1;
      }
   
   } else if (board[x][y] == 117 && (board[x][y-1] == 120 && board[x+1][y-1] != 120)){ // hit a bottom-right diamond
   
      if (board[x+1][y-1] == 114){
         board[x][y] = 32;
         return 1 + crawlan(x+1,y-1);
      } else {
         board[x][y] = 32;
         return 1;
      }
   
   } else if (board[x][y] == 117 && board[x][y-1] == 117){
      board[x][y] = 32;
      return 1 + crawlan(x, y-1);
   
   } else if (board[x][y] == 117 && board[x][y-1] != 117){
   board[x][y] = 32;
   return 1;
   } /* END OF UPWARD SCORE CRAWLER */
   /* BEGINNING OF LEFTWARD SCORE CRAWLER */
   else if (board[x][y] == 108 && x == 0){
      //check to see if we hit the left edge of the board
      
      if (board[width-1][y] == 108){ 
         board[x][y] = 32;
         return 1 + crawlan(width-1, y); 
      } else {
         board[x][y] = 32;
         return 1;
      }
      // now check to see if we hit a bottom-right diamond
   } else if (board[x][y] == 108 && (board[x-1][y] == 120 && board[x-1][y+1] != 120)){
      if (board[x-1][y+1] == 100){
         board[x][y] = 32;
         return 1 + crawlan(x-1, y+1);
      } else {
         board[x][y] = 32;
         return 1;
      }   
   
   //now check to see if we hit a top-right diamond
   } else if (board[x][y] == 108 && (board[x-1][y] == 120 && board[x-1][y-1] != 120)){
   
      if (board[x-1][y-1] == 117){
         board[x][y] = 32;
         return 1 + crawlan(x-1,y-1);
      } else {
         board[x][y] = 32;
         return 1;
      }
   
   } else if (board[x][y] == 108 && board[x-1][y] == 108){
      board[x][y] = 32;
      return 1 + crawlan(x-1, y);
   } else if (board[x][y] == 108 && board[x-1][y] != 108){
      board[x][y] = 32;
      return 1;
   } /* END LEFT CRAWLING BLOCK*/
     /* BEGIN DOWN-CRAWLING BLOCK */
   else if (board[x][y] == 100 && y == height-1){ //check to see if we hit the bottom edge of the board
      
      if (board[x][0] == 100){
         board[x][y] = 32;
         return 1 + crawlan(x,0);
      } else {
         board[x][y] = 32;
         return 1;
      }
      
   } else if (board[x][y] == 100 && (board[x][y+1] == 120 && board[x-1][y+1] != 120)){ //top-left diamond
   
      if (board[x-1][y+1] == 108){
         board[x][y] = 32;
         return 1 + crawlan(x-1,y+1);
      } else {
         board[x][y] = 32;
         return 1;
      }
   
   } else if (board[x][y] == 100 && (board[x][y+1] == 120 && board[x+1][y+1] != 120)){ //top-right diamond
   
      if (board[x+1][y+1] == 114){
         board[x][y] = 32;
         return 1 + crawlan(x+1, y+1);
      } else {
         board[x][y] = 32;
         return 1;
      }
   
   } else if (board[x][y] == 100 && board[x][y+1] == 100){
      board[x][y] = 32;
      return 1 + crawlan(x, y+1);
   } else if (board[x][y] == 100 && board[x][y+1] != 100){
      board[x][y] = 32;
      return 1;
      /* END DOWN CRAWLING BLOCK */
      /* BEGIN RIGHT-CRAWLING BLOCK */
   } else if (board[x][y] == 114 && x == width-1){ //check to see if we hit the edge of the board
      if (board[0][y] == 114){
         board[x][y] = 32;
         return 1 + crawlan (0,y);
      } else {
         board[x][y] = 32;
         return 1;
      }
   } else if (board[x][y] == 114 && (board[x+1][y] == 120 && board[x+1][y-1] != 120)){ //hit top-left diamond
   
      if (board[x+1][y-1] == 117){
            board[x][y] = 32;
            return 1 + crawlan(x+1, y-1);
         } else {
            board[x][y] = 32;
            return 1;
         }
   
   } else if (board[x][y] == 114 && (board[x+1][y] == 120 && board[x+1][y+1] != 120)){ //hit bottom-left diamond
   
      if (board[x+1][y+1] == 100) {
         board[x][y] = 32;
         return 1 + crawlan(x+1,y+1);
      } else {
         board[x][y] = 32;
         return 1;
      }
   
   } else if (board[x][y] == 114 && board[x+1][y] == 114){
      board[x][y] = 32;
      return 1 + crawlan(x+1, y);
   } else if (board[x][y] == 114 && board[x+1][y] != 114){
      board[x][y] = 32;
      return 1;
   }
}

int playgame(int x, int y){

   int pointeeX, pointeeY;
   int movescore = 0;
   
   if (board[x][y] == 117){ // pointing up
      /* BEGIN UPWARD MOVEMENTS */
      if ( y == 0 ){
         //pointing at the top of the board
         pointeeX = x;
         pointeeY = height-1;

      } else if ((board[x][y-1] == 120) && (board[x+1][y-1] != 120)){
         //pointing at bottom-right diamond
         pointeeX = x+1;
         pointeeY = y-1;
         //check to see if this will be a slide through a diamond
         if (board[pointeeX][pointeeY] == 32){
            board[x][y] = 32;
            board[pointeeX][pointeeY] = 114;
            return -1;
         } else if (board[pointeeX][pointeeY] == 114){ // check if we annhilate through the diamond
            return power2(crawlan(x, y));
         } else if (board[x][y] == board[pointeeX][pointeeY]) { 
            board[pointeeX][pointeeY] = 100; // don't get confused and annhilate same direction thru diamond
            return -1;
         }
         
      }  else if ((board[x][y-1] == 120) && (board[x-1][y-1] != 120)){
         //pointing at bottom-left diamond
         pointeeX = x-1;
         pointeeY = y-1;
         //check to see if this will be a slide through a diamond
         if (board[pointeeX][pointeeY] == 32){
            board[x][y] = 32;
            board[pointeeX][pointeeY] = 108;
            return -1;
         } else if (board[pointeeX][pointeeY] == 108) { 
         //check if we annhilate through the diamond
            return power2(crawlan(x, y));
         
         } else if (board[x][y] == board[pointeeX][pointeeY]){
            board[pointeeX][pointeeY] = 100; // don't get confused and annhilate same direction thru diamond
            return -1;
         }
      } else {
         pointeeX = x;
         pointeeY = y-1;
      }
      
      if (board[x][y] == board[pointeeX][pointeeY]){ // check to see if we have an annhilate
         return power2(crawlan(x,y));
      } else if (board[pointeeX][pointeeY] == 32){ //check if we are pointing at an empty space
         board[pointeeX][pointeeY] = board[x][y];
         board[x][y] = 32;
         return -1;
      } 
      
      /* END UPWARD MOVEMENTS */  
      }      
      
      
    else if (board[x][y] == 100){ //pointing down
   /* BEGIN DOWNARD MOVEMENTS */
   
      if (y == height-1){ //check to see if we are at edge of the board
         pointeeX = x;
         pointeeY = 0;
      } else if (board[x][y+1] == 120 && board[x-1][y+1] != 120){
      // top-left diamond tile
         pointeeX = x-1;
         pointeeY = y+1;
         
         // check to see if this will be a diamond slide
         if (board[pointeeX][pointeeY] == 32){
            board[x][y] = 32;
            board[pointeeX][pointeeY] = 108;
            return -1;
         } else if (board[pointeeX][pointeeY] == 108){ //check for annhilate thru diamond
            return power2(crawlan(x,y));         
         } else if (board[pointeeX][pointeeY] == board[x][y]){ // flip thru diamond
            board[pointeeX][pointeeY] = 117;
            return -1;
         }
      } 
      
      else if (board[x][y+1] == 120 && board[x+1][y+1] != 120) {
      // top-right diamond
         pointeeX = x+1;
         pointeeY = y+1;
         
         //check to see if this will be a diamond slide
         if (board[pointeeX][pointeeY] == 32){
            board[x][y] = 32;
            board[pointeeX][pointeeY] = 114;
            return -1;
         } else if (board[pointeeX][pointeeY] == 114){ // diamond annhilate
            return power2(crawlan(x,y));
         } else if (board[x][y] == board[pointeeX][pointeeY]){ // diamond flip
            board[pointeeX][pointeeY] = 117;
            return -1;         
         }
         
         
      } else {
         pointeeX = x;
         pointeeY = y+1;
      }
      
      if (board[x][y] == board[pointeeX][pointeeY]){
         return power2(crawlan(x,y));
      } else if (board[pointeeX][pointeeY] == 32){
         board[pointeeX][pointeeY] = board[x][y];
         board[x][y] = 32;
         return -1;
      }
      
      // END DOWNWARD MOVEMENTS
      
   } else if (board[x][y] == 108){ //pointing left
      // BEGIN LEFTWARD MOVEMENTS


      if (x == 0){
         // check to see if we've hit the left-edge of the board
         pointeeX = width-1;
         pointeeY = y;
      } else if (board[x-1][y] == 120 && board[x-1][y-1] != 120){
         // check for top-right diamond
         pointeeX = x-1;
         pointeeY = y-1;
         
         //check if this is a diamond slide
         if (board[pointeeX][pointeeY] == 32){
            board[x][y] = 32;
            board[pointeeX][pointeeY] = 117;
            return -1;         
         }  else if (board[pointeeX][pointeeY] == 117){ //anhilate thru diamond
            return power2(crawlan(x,y));
         } else if (board[pointeeX][pointeeY] == board[x][y]){ //flip thru diamond
            board[pointeeX][pointeeY] = 114;
            return -1;
         }
                         
      } else if (board[x-1][y] == 120 && board[x-1][y+1] != 120){
         //bottom-right diamond
         pointeeX = x-1;
         pointeeY = y+1;
         
         // check if this is a diamond slide
         if (board[pointeeX][pointeeY] == 32){
            board[x][y] = 32;
            board[pointeeX][pointeeY] = 100;
            return -1;
         } else if (board[pointeeX][pointeeY] == 100){
            return power2(crawlan(x,y)); //annhilate thru diamond
         } else if (board[pointeeX][pointeeY] == board[x][y]){
            board[pointeeX][pointeeY] = 114; // flip thru diamond
            return -1;
         }
      
      } else {
         pointeeX = x-1;
         pointeeY = y;
      }

      if (board[x][y] == board[pointeeX][pointeeY]){
         return power2(crawlan(x,y));
      } else if (board[pointeeX][pointeeY] == 32){
         board[pointeeX][pointeeY] = board[x][y];
         board[x][y] = 32;
         return -1;
      
      }

   /* END LEFTWARD MOVEMENT */

   } else if (board[x][y] == 114){ //pointing right
     // BEGIN RIGHT-WARD MOVEMENT 
      if (x == width-1){
         // check to see if we hit the edge of the board
         pointeeX = 0;
         pointeeY = y;
      } else if (board[x+1][y] == 120 && board[x+1][y-1] != 120){
         // top-left diamond
         pointeeX = x+1;
         pointeeY = y-1;
         
         // check for a dimaond-slide
         if (board[pointeeX][pointeeY] == 32){
            board[x][y] = 32;
            board[pointeeX][pointeeY] = 117;
            return -1;
         } else if (board[pointeeX][pointeeY] == 117){
            return power2(crawlan(x,y)); //diamond annhilate
         } else if (board[x][y] == board[pointeeX][pointeeY]){
            board[pointeeX][pointeeY] = 108; // diamond flip
            return -1;
         }
      
      } else if (board[x+1][y] == 120 && board[x+1][y+1] != 120){
         //check for bottom-left diamond
         pointeeX = x+1;
         pointeeY = y+1;
         
         // check for a diamond-slide
         if (board[pointeeX][pointeeY] == 32){
            board[x][y] = 32;
            board[pointeeX][pointeeY] = 100;
            return -1;
         } else if (board[pointeeX][pointeeY] == 100){
            return power2(crawlan(x,y)); //anhilate thru diamond
         } else if (board[x][y] == board[pointeeX][pointeeY]){
            board[pointeeX][pointeeY] = 117;
            return -1;
         }
      
      } else {
         pointeeX = x+1;
         pointeeY = y;
      
      }
      
      if (board[x][y] == board[pointeeX][pointeeY]){
         return power2(crawlan(x,y));
      } else if (board[pointeeX][pointeeY] == 32){
         board[pointeeX][pointeeY] = board[x][y];
         board[x][y] = 32;
         return -1;
      }
      
     
   } else if (board[x][y] == 120) {
      return 0;
   } else if (board[x][y] == 32){
      return 0;
   }
   
   // if we make it thus far, just flip the pointee
   if (board[pointeeX][pointeeY] == 100){
      board[pointeeX][pointeeY] = 117;
      return -1;
   } else if (board[pointeeX][pointeeY] == 108) {
      board[pointeeX][pointeeY] = 114;
      return -1;
   } else if (board[pointeeX][pointeeY] == 114) {
      board[pointeeX][pointeeY] = 108;
      return -1;
   } else if (board[pointeeX][pointeeY] == 117){
      board[pointeeX][pointeeY] = 100;
      return -1;
   }
   
   

}

void make_rboard(int w, int h){

   // randomly assign tiles all over the board
   for (int i = 0; i < h; i++){   
      for (int j = 0; j < w; j++) {
         
         int r = rand()%4 + 1;
         char tile;
         //decodes to ascii
         if (r == 1){
            tile = 117;  
         }
         
         if (r == 2){
            tile = 100;
         }
      
         if (r == 3){
            tile = 108;
         }
         
         if (r == 4){
            tile = 114;
         }
         
         board[i][j] = tile;
         
         
      }   
   }

   // pad the end of the board with a 'end of board' value
   // vertically
   for (int k = 0; k < h; k++){
      board[h][k] = -1;
   }

   // pad the end of the board with a 'end of board' value
   // horizontally
   for (int r = 0; r < w; r++){
      board[r][w] = -1;
   }
   
   // fill the 2x2 centre with diamond values
   // the top left corner of the square will be
   // determined by (h - 2) / 2 and the other 3
   // tiles will be determined in reference to this
   int tlx = (h - 2) / 2;
   int tly = (w - 2) / 2;
   // 120 represents the ascii 'x'
   board[tlx][tly] = 120;
   board[tlx+1][tly] = 120;
   board[tlx][tly+1] = 120;
   board[tlx+1][tly+1] = 120;

}

// a function for printing the board
void bprint(int x, int y){ 
   
   for(int j=0; j<y; j++){
        
    // prints the numbers on the y axis and spacing
      if (y-j > 9) printf("%d |", y-j);
      else printf("%d  |", y-j);
      
      for (int i = 0; i < x; i++){
      printf("%c  ", board[i][j]);
      
      }
      
      printf("\n");
   }
   
    //prints numbers on the x axis and spacing
   printf("    ");
   
   for (int k = 0; k < (x-1)*3 +2; k++) printf("-");
      printf("\n");
      printf("    ");
      
   for (int l = 0; l<x; l++){
     if (l+1 < 10) printf("%d  ", l+1);
     else printf("%d ", l+1);
   }
   printf("\n");
  
}

void log_move(int x, int y){  
   fprintf(output, "%d %d %d \n", x, y, score); //logs the move the player made
}


void log_board(int x, int y){  
   fprintf(output, "\n"); 
   fprintf(output, "student 1 info\n"); //these need to be changed
   fprintf(output, "student 2 info\n");
   fprintf(output, "student 3 info\n");
   fprintf(output, "\n"); 

   fprintf(output, "%d %d \n", y, x); //prints dimensions of the board
   
   // prints the board to log file
   for(int j=0; j<y; j++){
      for (int i = 0; i < x; i++){    
       fprintf(output, "%c  ", board[i][j]);    
      }
      
      fprintf(output ,"\n");
   } 
   fprintf(output ,"\n");
   fprintf(output, "START \n");
}


int startgame(){


   // here we prompt the user to decide how they want the board to be defined
   int userchoice = -1;
   while(userchoice != 1 && userchoice != 2) {   
   system("clear");
   printf("Please select one of the following options by\n");
   printf("entering the associated number:\n");
   printf("1. User-specified board dimensions\n2. Read board from input file\n");
   scanf("%d", &userchoice);   
   }
 
   //variables for width and height of the board
   int w = -1;
   int h = -1;
  
   //variable that contains the output file
   output = fopen("log.txt", "a+");
  
   if (userchoice == 1){      
      while (((w % 2) != 0) || (w < 4 || w > 20)){
      system("clear");
      printf("Please enter the width of the board(between 4 and 20 and even): ");
      scanf("%d", &w);     
       }
      while ((h < 4 || h > 20) || ((h % 2) != 0)){
      system("clear");
      printf("Please enter the height of the board(between 4 and 20 and even): ");
      scanf("%d", &h);
      }
      make_rboard(h,w);
      log_board (w,h);
   }
   
   else if (userchoice == 2) {
      FILE *input;
      char file[13];
      system("clear");
      printf("\n\n Please specify a file name (xxxxxx.yyy): ");
      scanf("%s", file);
      
      if ((input = fopen(file, "r")) == NULL) {
         printf("\nFilename invalid\n");   
      }
   
      h = 0;
      w = 0;
   
      fscanf(input, "%d", &h);
      fscanf(input, "%d", &w);
      fgetc(input);
      
      //read board in from file   
      for (int i = 0; i<h; i++){
         for (int j = 0; j<w; j++){
           char in;
           fscanf(input, "%c", &in);
           board[j][i]= in;
         }
         fgetc(input); //closes file
    }
   
    fclose(input);
    
    log_board (w,h); //logs board
       
   }
   
   
   while(userchoice != 3 && userchoice != 4) {   
   system("clear");
   printf("Please select one of the following options by\n");
   printf("entering the associated number:\n");
   printf("3. Interactive Play\n4. Computer Play\n");
   scanf("%d", &userchoice);   
   }
   
   width = w;
   height = h;
   
   if (userchoice == 3){
      system("clear");
      bprint(w, h);
      int x;
      int y;
      int game = 1;  
                     
      while (game){ 
         
         printf("Score : %d\n", score);
         printf("Please enter move: x y, or 0 0 to quit \n");
        
         scanf(" %d %d", &x, &y);

         if (x == 0 && y ==0){ //exits the game
             fprintf (output, "END");
             game = 0;
             }
                
         else if (1 <= x && x <= w && 1 <= y && y <= h){ //checks if input falls in a valid range
      
            score += playgame(x-1,h-y); //updates score 
            log_move(x,y); //prints move to log file
            system("clear");
            bprint(w,h); 
         }

         else {
            printf("Invalid move, try again \n");
         }
            
      
      
      }
      
      
      
   }
   
      else if (userchoice == 4){
      system("clear");
      bprint(w,h);
      int game = 1;
      
      while (game){
         
      system("clear");
      bprint(w,h);   
      
      int playX = -1;   
      int playY = -1;
      int tempscore = 0;
         
         for (int i = 0; i<w; i++){
            for (int j =0; j<h; j++){ 
               int calcscore = aiplaygame(i,j);
               if (calcscore > tempscore){
                  playX = i;
                  playY = j;
                  tempscore = calcscore;
               }
            }
         }
         
         if (tempscore == -1){
            printf ("No move moves\n");
            printf("score: %d\n", score);
            game = 0;
         }
         
         else {
          printf("score: %d\n", score);
          printf("ai move: %d %d\n",playX+1,h-playY);  
          score += playgame(playX, playY);
          log_move(playX+1, h-playY); 
          

         }
         
         
         //ai makes a move 
         //ai decides when game is done, sets game = 0
         //use log_move to log
         //probably want to print out the moves the AI is making, as well as the updated score
      
     // sleep(1); //sleeps for one second
      
      }
   }
      
      
   
   
   
   fclose(output); //closes output file

}


int main(){
   sRand(); //seeds the random generator
   startgame(); //starts the game
   return 1;
      
}


