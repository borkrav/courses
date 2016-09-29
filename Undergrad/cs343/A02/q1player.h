#include <uC++.h>
#include "q1printer.h"

_Coroutine Player {
		Player *left;
		Player *right;
		int pid;
		Printer * pr;
		unsigned int myDeck;
		void main();

  public:	
    Player( Printer &printer, unsigned int id );
		~Player();
    void start( Player &lp, Player &rp );
    void play( unsigned int deck );
};
