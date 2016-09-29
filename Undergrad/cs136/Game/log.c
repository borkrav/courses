#include <stdio.h>
#include <stdlib.h>
#include <time.h>


char board[25][25];  //a two dimensional array of charecter values
int score = 0;
FILE *output;

void sRand()
{
   time_t timer = 0;
   time(&timer);   
   srand(timer);
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




void log_move(int x, int y){  
   fprintf(output, "%d %d %d \n", x, y, score);
}

void log_board(int x, int y){
  
   fprintf(output, "student 1 info\n");
   fprintf(output, "student 2 info\n");
   fprintf(output, "student 3 info\n");
   fprintf(output, "\n"); 

   fprintf(output, "%d %d \n", y, x);
   
    for(int i = 0; board[i][0] != -1; i++){
      for (int j = 0; board[0][j] != -1; j++){
         fprintf(output, "%c", board[i][j]);
      }
      fprintf(output ,"\n");
   }

 
}
   
   

int startgame(){

 
    output = fopen("log.txt", "a+");
   
 
   //variables for width and height of the board
   int w = -1;
   int h = -1;
   
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
      make_rboard(w,h);
      
      log_board (w,h); //board is logged as soon as generated

   bprint(); //prints board after mode selection, for testing purposes only.
   
      
   
   int x;
   int y;
   

   
   //first move is made
   fprintf(output, "\n");
   
   fprintf (output, "START \n");

    while (1 == scanf(" %d", &x)){
       scanf(" %d", &y);
       log_move(x, y);
    }
    
    //last move is made
    
    fprintf(output, "END");
    fclose (output);
    

}










int main(){
   
   startgame();
   return 1;
      
}


