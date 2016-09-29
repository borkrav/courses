#include "q1player.h"
#include <uC++.h>
#include <iostream>
#include <string>
#include "PRNG.h"
#include <vector>
#include <utility>

PRNG randGen; 


void uMain::main() {

	//this is the default number of games
	int numOfGames = 5;

	//if we have too many arguments, error out
	if (argc > 3){
		std::cerr << "Usage: " << argv[0] << " [ number-of-games ( >= 0 ) [ random-seed ( > 0 ) ] ]" << std::endl;
		exit(0);
		
	}

	//if we have 2 arguments, set the seed and generate the number of games
	if (argc == 3){
		if (atoi(argv[1]) < 0 || atoi(argv[2]) <= 0){
			std::cerr << "Usage: " << argv[0] << " [ number-of-games ( >= 0 ) [ random-seed ( > 0 ) ] ]" << std::endl;
			exit(0);
		}
		randGen = PRNG(atoi(argv[2]));
		numOfGames = atoi(argv[1]);
	}

	//if we have 1 argument, set the seed to be the PID, and generate the number of games
	else if (argc == 2){
		if (atoi(argv[1]) < 0){
			std::cerr << "Usage: " << argv[0] << " [ number-of-games ( >= 0 ) [ random-seed ( > 0 ) ] ]" << std::endl;
			exit(0);
		}
		randGen = PRNG(getpid());
		numOfGames = atoi(argv[1]);
	}

	//if we have no arguments, just set the seed to be PID
	else {
		randGen = PRNG(getpid());
	}



	for (int i = 0; i < numOfGames; i++){

		//genarate number of players, number of cards, and the player who will start
		int numOfPlayers = randGen(2,10);
		int numOfCards = randGen(10,200);
		int playerToStart = randGen(0,numOfPlayers-1);


		Printer p(numOfPlayers,numOfCards);

		std::vector<Player*> players = std::vector<Player*>(numOfPlayers);

		//puts players on the heap
		for (int i = 0; i < numOfPlayers; i++){
			Player *pl = new Player(p,i);
			players[i] = pl;
		}


		//starts all the players
		for (int i = 0; i < numOfPlayers; i++){
			if (i == 0)	{
				players[i]->start(*players[numOfPlayers-1], *players[i+1]);
			}
			else if (i+1 == numOfPlayers){
				players[i]->start(*players[i-1], *players[0]);
			}

			else {
				players[i]->start(*players[i-1], *players[i+1]);
			}

		
		} 
 
		//calls play on the game starting player
		players[playerToStart]->play(numOfCards);

		//deletes all players
		for (int i = 0; i < numOfPlayers; i++){
			delete players[i];
		}
		
		//prints the padding between games
		if (i != numOfGames-1){
			std::cout << std::endl;
			std::cout << std::endl;
		}
	}


}


