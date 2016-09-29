#include <uC++.h>
#include <iostream>
#include "MPRNG.h"
#include "q1philosopher.h"
#include "q1table.h"
#include "q1printer.h"

using namespace std;

MPRNG randGen;

void uMain::main() {

	//set default parameters
	int philosophers = 5;
	int noodles = 30;
	int seed = getpid();

	//get arguments, if any are given
	try{

		switch(argc){
			case 4:
				if (atoi(argv[3]) <= 0) throw -1;
				seed = atoi(argv[3]);
			//Fall though
			case 3:
				if (atoi(argv[2]) <= 0) throw -1;
				noodles = atoi(argv[2]);
			//Fall though
			case 2:
				if (atoi(argv[1]) <= 1) throw -1;
				philosophers = atoi(argv[1]);
			//Fall though
			case 1:
				break;
			default:
				throw(-1);
		}

	} catch (int e){
		if (e == -1){
				//If the parameters are incorrect, crash
				std::cerr << "Usage: " 
									<< argv[0] 
									<< " [ philosophers (> 1) [ noodles (> 0) [ Seed (> 0) ] ] ]" 
									<< std::endl;
				exit(0);
		}
	}

	//seed the random number generator
	randGen.seed(seed);

	Printer printer(philosophers);
	Table table(philosophers, printer);

	vector <Philosopher*> philTasks = vector <Philosopher*>(philosophers);

	//initialize the philosophers
	for (int i = 0; i < philosophers; i++){
		philTasks[i] = new Philosopher(i, noodles, table, printer);
	}

	//delete the philosophers
	for (int i = 0; i < philosophers; i++){
		delete philTasks[i];
	}

	cout << "***********************" << endl;
	cout << "Philosophers terminated" << endl;
	
}
