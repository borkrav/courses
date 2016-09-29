#include <uC++.h>
#include <iostream>
#include "MPRNG.h"
#include "q1tallyVotes.h"
#include "q1voter.h"
#include "q1printer.h"

using namespace std;

MPRNG randGen;

void uMain::main() {

	//set default parameters
	int voters = 6;
	int groupSize = 3;
	int seed = getpid();

	//get arguments, if any are given
	try{

		switch(argc){
			case 4:
				if (atoi(argv[3]) <= 0) throw -1;
				seed = atoi(argv[3]);
			//Fall though
			case 3:
				groupSize = atoi(argv[2]);
			//Fall though
			case 2:
				voters = atoi(argv[1]);
			//Fall though
			case 1:
				break;
			default:
				//wrong number of parameters
				throw(-1);
			}

		if (voters <= 0 || voters%groupSize != 0 || groupSize <= 0 || groupSize %2 != 1) throw -1;

	} catch (int e){
		if (e == -1){
				//If the parameters are incorrect, crash
				std::cerr
						<< "Usage: " 
						<< argv[0] 
						<< " Voters (> 0 & V mod G = 0, default 6)  Group (> 0 & odd, default 3)  Seed (> 0)" 
						<< std::endl;
				exit(0);
		}
	}

	//seed the random number generator
	randGen.seed(seed);

	//initialize tallier and printer
	Printer printer(voters);
	TallyVotes tallier(groupSize, printer);

	vector <Voter*> voterTasks = vector <Voter*>(voters);

	//initialize the voters
	for (int i = 0; i < voters; i++){
		voterTasks[i] = new Voter(i, tallier, printer);
	}

	//delete the voters
	for (int i = 0; i < voters; i++){
		delete voterTasks[i];
	}

	
}
