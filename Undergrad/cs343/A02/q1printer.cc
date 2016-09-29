#include "q1printer.h"


/* Initializes the printer
*	INPUTS
* 		const unsigned int NoOfPlayers - the number of players that will play
*			const unsigned int NoOfCards - the number of cards in play
* OUTPUTS
* 		void
*/
Printer::Printer( const unsigned int NoOfPlayers, const unsigned int NoOfCards ){
	players = NoOfPlayers;
	cards = NoOfCards;

	//creates the buffer that will hold information prior to flushing
	//this buffer is a vector of integrer pairs
	//the index in the vector represents the player, and the pair holds (cardsTaken, cardsLeft)

	buffer = std::vector<std::pair <int, int> >(players);

	//initializes the buffer with negative values so I know nothing is there
	for (int i = 0; i<buffer.size(); i++) buffer[i] = std::make_pair(-1,-1);

	//prints the header of the table
	std::cout << "Players: " << NoOfPlayers << "    " << "Cards: " << NoOfCards << std::endl;
	for (int i = 0; i<NoOfPlayers; i++){
		std::cout << "P" << i << "	";
	}
	std::cout << std::endl;

}

/* The print method 
*	INPUTS
* 		const unsigned int id - the id of the player
*			const unsigned int took - the number of cards the player took
* OUTPUTS
* 		void
*/
void Printer::prt( const unsigned int id, const unsigned int took ){

	//if the buffer slot is invalidated
	if (buffer[id].first == -1){
		
		//write to the buffer
		buffer[id].first = took;
		cards = cards - took;
		buffer[id].second = cards;

		//if there are no more cards left, flush
		if (cards == 0){
			flush();
		}
	}

	//if the buffer slot is not invalidated, ie there's already player info there
	else if (buffer[id].first != -1) {
		
		//flush		
		flush();

		//write to the buffer
		buffer[id].first = took;
		cards = cards - took;
		buffer[id].second = cards;

		//if there are no more cards left, flush again
		if (cards == 0){
			flush();
		}
	}

}


/* The flush method - prints the player info to the screen 
*	INPUTS
* 		none
* OUTPUTS
* 		void
*/
void Printer::flush(){


	for (int i = 0; i < buffer.size(); i++){

		//the buffer slot is invalid, the player has not played in this line
		if (buffer[i].first == -1){
			std::cout << "" << "	";
		}

		//the remaining cards is zero, the game is over
		else if (buffer[i].second == 0){
			std::cout << buffer[i].first << ":" << buffer[i].second << "#	";
		}

		//the remaining cards is not zero, and the player passed the cards to the right
		else if (buffer[i].second % 2 == 0) {
			std::cout << buffer[i].first << ":" << buffer[i].second << ">	";
		}

		//otherwise, the player passed the cards to the left
		else {
			std::cout << buffer[i].first << ":" << buffer[i].second << "<	";
		}

		//invalidate the buffer since we printed the player info
		buffer[i].first = -1;
	}
	
	std::cout << std::endl;

}
