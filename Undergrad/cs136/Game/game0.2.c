#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


char board[25][25];  //a two dimensional array of charecter values
int height;
int width;

void sRand()
{
   time_t timer = 0;
   time(&timer);   
   srand(timer);
}

int crawlan(int x, int y){
   
   /* BEGIN OF UPWARD SCORE CRAWLER */
   //check if we've crawled UP into edge of the board
   if ((board[x][y] == 117) && (y == 0)){
      
      if ((board[x][height-1] == 117){
         board[x][y] = 32;
         return 1 + crawlan(x, height-1)
      } else {
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
   else if (board[x][y] == 108 && x = 0){
      
      
      if (board[width-1][y] == 108){ //check to see if we hit the left edge of the board
         board[x][y] = 32;
         return 1 + crawlan(x, width);
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
         }         
      } else {
         pointeeX = x;
         pointeeY = y-1;
      }
      
      if (board[x][y] == board[pointeeX][pointeeY]){ // check to see if we have an annhilate
         return pow (2, crawlan(x,y));
      } else if (board[pointeeX][pointeeY] == 32){ //check if we are pointing at an empty space
         board[pointeeX][pointeeY] = board[x][y];
         board[x][y] = 32;
         return -1;
      } 
      
      /* END UPWARD MOVEMENTS */  
      }      
      
      
   } else if (board[x][y] == 100){ //pointing down
   /* BEGIN DOWNARD MOVEMENTS */
   
      if (x == height-1){ //check to see if we are at edge of the board
         pointeeX = x;
         pointeeY = 0;
      } else if (board[x][y-1] == 120 && board[x-1][y+1] != 120){
      // top-left diamond tile
         pointeeX = x-1;
         pointeeY = y+1;
         
         // check to see if this will be a diamond slide
         if (board[pointeeX][pointeeY] == 32){
            board[x][y] = 32;
            board[pointeeX][pointeeY] = 108;
            return -1;
         }
         
      } else if (board[x][y-1] == 120 && board[x+1][y+1] != 120) {
      // top-right diamond
         pointeeX = x+1;
         pointeeY = y+1;
         
         //check to see if this will be a diamond slide
         if (board[pointeeX][pointeeY] == 32){
            board[x][y] = 32;
            board[pointeeX][pointeeY] = 114;
            return -1
         }
         
         
      } else {
         pointeeX = x;
         pointeeY = y+1;
      }
      
      if (board[x][y] == board[pointeeX][pointeeY]){
         return pow(2, crawlan(x,y));
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
         }
      
      } else {
         pointeeX = x-1;
         pointeeY = y;
      }

      if (board[x][y] == board[pointeeX][pointeeY]){
         return pow (2, crawlan(x,y));
      } else if (board[pointeeX][pointeeY] == 32){
         board[pointeeX][pointeeY] = board[x][y];
         board[x][y] = 32;
         return -1;
      
      }

   /* END LEFTWARD MOVEMENT */

   } else if (board[x][y] == 114){ //pointing right
     // BEGIN RIGHT-WARD MOVEMENT 
      if (x == witdh-1){
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
         }
      
      } else if (board[x+1][y] == 120 && board[x+1][y+1] != 120){
         //check for bottom-left diamond
         pointeeX = x+1;
         pointeeY = y+1;
         
         // check for a diamond-slide
         if (board[pointeeX][pointeeY] = 32){
            board[x][y] = 32;
            board[pointeeX][pointeeY] = 100;
            return -1;
         }
      
      } else {
         pointeeX = x+1;
         pointeeY = y;
      
      }
      
      if (board[x][y] == board[pointeeX][pointeeY]){
         return pow (2, crawlan(x,y));
      } else if (board[pointeeX][pointeeY] == 32)}
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
   for (int i = 0; i < h; i++){2   
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
      board[w][k] = -1;
   }

   // pad the end of the board with a 'end of board' value
   // horizontally
   for (int r = 0; r < w; r++){
      board[r][h] = -1;
   }
   
   // fill the 2x2 centre with diamond values
   // the top left corner of the square will be
   // determined by (h - 2) / 2 and the other 3
   // tiles will be determined in reference to this
   int tlx = (w - 2) / 2;
   int tly = (h - 2) / 2;
   // 120 represents the ascii 'x'
   board[tlx][tly] = 120;
   board[tlx+1][tly] = 120;
   board[tlx][tly+1] = 120;
   board[tlx+1][tly+1] = 120;

}


//prints the board
void bprint(){
   for(int i = 0; board[i][0] != -1; i++){
      for (int j = 0; board[0][j] != -1; j++){
         printf("%c", board[i][j]);
      }
      printf("\n");
   }
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
 
   if (userchoice == 1){      
      while (((w % 2) != 0) || (w < 4 || w > 20)){
      system("clear");
      printf("Please enter the width of the board(between 4 and 20 and even): ");
      scanf("%d", &w);
      width = w;     
       }
      while ((h < 4 || h > 20) || ((h % 2) != 0)){
      system("clear");
      printf("Please enter the height of the board(between 4 and 20 and even): ");
      scanf("%d", &h);
      height = h;
      }
      make_rboard(w,h);
   }
   
   else {
      FILE *input;
      char file[13];
      system("clear");
      printf("\n\n Please specify a file name (xxxxxx.yyy): ");
      scanf("%s", file);
      
      if ((input = fopen(file, "r")) == NULL) {
         printf("\nFilename invalid\n");   
      }
   
       h=0;
       w=0;
   
      fscanf(input, "%d", &h);
      fscanf(input, "%d", &w);
      fgetc(input);
         
      for (int i = 0; i<h; i++){
         for (int j = 0; j<w; j++){
           fscanf(input, "%c", &board[i][j]);
         }
         fgetc(input);
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

       height = h;
       width = w;
       fclose(input);
   }
   
   bprint(); //prints board after mode selection, for testing purposes only.

}


int main(){
   
   startgame();
   return 1;
      
}


