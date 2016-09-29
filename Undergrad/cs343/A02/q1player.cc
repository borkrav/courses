#include "q1player.h"

//the randGen global that's defined in q1main.cc
extern PRNG randGen; 

/* The player constructor
*	INPUTS
* 		Printer &printer - the reference to the printer object
*			unsigned int id - the id of the player
*/
Player::Player( Printer::Printer &printer, unsigned int id ){
	pr = &printer;
	pid = id;
}


// a stub for the destructor
Player::~Player(){
}


//the coroutine main
void Player::main(){
	
	//START RESUMES HERE
	suspend();	//RETURNS CONTROL TO MAIN
	
	//PLAY RESUMES HERE
	while (true){
		int choice = 0;	
		//if there are more then 8 cards left, pick the number to take
		if (myDeck > 8)	choice = randGen( 1, 8 );
		//else take all remaining cards and win
		else choice = myDeck;

		//tell printer to print the player's play
		pr->prt(pid, choice);
		
		int remaining = myDeck-choice;

		//if the game is over, break out of this loop, finish main execution and return control to 			//program main		
		if (remaining == 0) break;
		//else choose left or right
		else if (remaining % 2 == 0) right->play(myDeck-choice);
		else if (remaining % 2 == 1) left->play(myDeck-choice);

	}

}

/* The start function - starts a player
*	INPUTS
* 		Player &lp - the reference to the player on the left
*			Player &rp - the reference to the player on the right
*	OUTPUT
*			void
*/
void Player::start( Player &lp, Player &rp ){
	left = &lp;
	right = &rp;	
	resume(); //START RESUME
}

/* The play function
*	INPUTS
* 		unsigned int deck - the number of cards in the deck
*	OUTPUT
*			void
*/
void Player::play( unsigned int deck ){
	
	myDeck = deck;
	
	resume(); //PLAY RESUME
}

