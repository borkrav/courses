#ifndef __TRUCK__
#define __TRUCK__

#include "common.h"

_Task BottlingPlant;
_Task VendingMachine;
_Task NameServer;

_Task Truck {
    void main();
		Printer* m_printer;
		BottlingPlant* m_plant;

		unsigned int m_numMachines;
		unsigned int m_maxStock;

		VendingMachine** m_machines;
		unsigned int* m_cargo;

		int size();

  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
		~Truck();
};

#endif
