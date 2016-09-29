#include <uC++.h>
#include <iostream>
#include "MPRNG.h"
#include "config.h"
#include "common.h"

#include "bank.h"
#include "parent.h"
#include "WATCardOffice.h"
#include "nameServer.h"
#include "vendingMachine.h"
#include "bottlingPlant.h"
#include "student.h"

using namespace std;

MPRNG number_generator;
	
void uMain::main() {

	//set default parameters
	string configFile = "soda.config";
	int seed = getpid();

	//get arguments, if any are given
	try{

		switch(argc){
			case 3:
				if (atoi(argv[2]) <= 0) throw -1;
				seed = atoi(argv[2]);
			//Fall though
			case 2:
				configFile = argv[1];
			//Fall though
			case 1:
				break;
			default:
				//wrong number of parameters
				throw(-1);
			}

		if (access(configFile.c_str(), F_OK) != 0 || access(configFile.c_str(), R_OK) != 0) throw -2;

	} catch (int e){
		if (e == -1){
				//If the parameters are incorrect, crash
				std::cerr
						<< "Usage: " 
						<< argv[0] 
						<< " [ config-file [ random-seed (> 0) ] ]" 
						<< std::endl;
				exit(0);
		}
		else if (e == -2){
			cout << "Error: could not open input file \"" << configFile << "\"" << endl;
				exit(0);
		}
	}

	//seed the random number generator
	number_generator.seed(seed);
	
	ConfigParms config;

	processConfigFile(configFile.c_str(), config);

	Printer *printer = new Printer(config.numStudents, 
		config.numVendingMachines, 
		config.numCouriers);

	Bank b( config.numStudents );
	Parent* p = new Parent( *printer, b, config.numStudents, config.parentalDelay );
	WATCardOffice* wco = new WATCardOffice( *printer, b, config.numCouriers);
	NameServer* ns = new NameServer( *printer, config.numVendingMachines, config.numStudents);
	
	vector<VendingMachine*> vms;
	for( unsigned int i = 0; i < config.numVendingMachines; ++i )
		vms.push_back( 
			new VendingMachine( *printer, *ns, i, config.sodaCost, config.maxStockPerFlavour) 
		);
	
	BottlingPlant* bp = new BottlingPlant( *printer, *ns, config.numVendingMachines,
                 config.maxShippedPerFlavour, config.maxStockPerFlavour,
                 config.timeBetweenShipments );

	vector<Student*> ss;
	for( unsigned int i = 0; i < config.numStudents; ++i )
		ss.push_back( new Student( *printer, *ns, *wco, i, config.maxPurchases ) );

	for( unsigned int i = 0; i < ss.size(); ++i )
		delete ss[i];

	delete bp;

	for( unsigned int i = 0; i < vms.size(); ++i )
		delete vms[i];

	delete ns;
	delete wco;
	delete p;
	delete printer;
}
