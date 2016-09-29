#include "newgame.h"
#include "playnewgame.h"

int ub;
int lb;
int num;
char checker;

int bisection(){

checker = guess(lb+(ub-lb)/2);

while (checker != 'r'){
if (checker == 'h'){
ub = lb+(ub-lb)/2;
num += 1;
}

else if (checker == 'l' && ub-lb == 1){
lb = ub;
num+=1;
}

else if (checker == 'l'){
lb = lb+(ub-lb)/2;
num+=1 ;
}

checker = guess(lb+(ub-lb)/2);


}
return num;
}


int playgame(int n){
startgame(n);
ub = n;
lb = 0;
num = 0;
int moves = bisection();
return moves;
}

