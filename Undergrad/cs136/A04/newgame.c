#include "newgame.h";

int secret = 0;
char out;

int startgame(int n){
secret = 1;
}

char guess(int x){

if (x == secret){out = 'r';}
else if (x < secret){out = 'l';}
else if (x > secret){out = 'h';}

return out;
}
