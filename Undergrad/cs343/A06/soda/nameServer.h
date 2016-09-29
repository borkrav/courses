#ifndef __NAMESERVER__
#define __NAMESERVER__

#include "common.h"

_Task VendingMachine;

_Task NameServer {
		Printer *m_printer;


		unsigned int m_machineCount, m_numMachines;
		VendingMachine** m_machines;
		unsigned int *m_offsets;	

    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
		~NameServer();

    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};


#endif
