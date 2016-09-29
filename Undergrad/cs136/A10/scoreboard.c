#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct record {
   char name[21];
   int score;
};

struct record scoreboard[1000];
int posn = 0;
int quit = 0;
int highscore = -1000000000;
int commands = 0;


void get_token(char input[21]){
   
   int i = 0;
   int end = 0;
   
   for (i= 0; i<20; i++){
     int token; 
     token = getchar();
     
     if (token == EOF){
         quit = 1;
         end = 1;
         break;
      }
     
     input[i] = token;
   
     if (input[i] == '\n' || input[i] == 0 || input[i] == 32){
        end = 1;
        break; 
      } 
   }
   
   input[i] = 0;
   
   if(end == 0){
      char c = 0;
      while (c != '\n'){
         if (c == ' ') break;
         c = getchar();
      }
      c = 0;
   }
}  


int find_name(char target[21]){
   
   for(int i = 0; i< posn; i++){
      if (strcmp (target, scoreboard[i].name) == 0) return i;
   }
   
   return -1;
   
}

void findhighscore(){
   for(int i = 0; i<posn; i++){
      if (scoreboard[i].score > highscore) {
         highscore = scoreboard[i].score;
      }
   }
}


int main(){

while (quit !=1 && commands < 1000){
   
   char command[21];
   get_token(command);
   
   if (strcmp(command, "score") == 0){
      
      char name[21];
      get_token(name);
      int score = -1000000000;
      scanf("%d", &score);
      
      int repeat = find_name(name);
      
      if (repeat == -1){
         strcpy(scoreboard[posn].name, name);
         scoreboard[posn].score = score;
         posn+=1;
      }
      
      else if (score > scoreboard[repeat].score){
         scoreboard[repeat].score = score;
      }

      commands+=1;
            
   }
   
   else if (strcmp (command, "best") == 0){
      
      char target[21];
      get_token(target);
      
      int location = find_name(target);
      
      if (location == -1) printf("best %s ?\n", target);
      
      else printf("best %s %d\n", target, scoreboard[location].score);
      
      commands+=1;
   }
   
   else if (strcmp (command, "highscore") == 0){
      findhighscore();
      if (posn == 0 || highscore == - 1000000000) printf("highscore ?\n");
      
      else{
         printf("highscore %d\n", highscore);
      }
         commands+=1;
      
   }
   
   else if(strcmp (command, "disqualify") == 0){
      char target[21];
      get_token(target);
      
      int location = find_name(target);
      
      if (location != -1){
      
      if (location == posn-1) posn-=1;
      else{
         strcpy(scoreboard[location].name, scoreboard[posn-1].name);
         scoreboard[location].score = scoreboard[posn-1].score;
         posn-=1;
      }
      highscore = -1000000000;
      commands +=1;
   }
}
}

   return 1;
}

