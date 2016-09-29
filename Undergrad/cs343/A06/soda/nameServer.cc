#include "nameServer.h"
#include "vendingMachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents )
	: m_printer( &prt ), m_machineCount( 0 ), m_numMachines( numVendingMachines ) {

	m_offsets = new unsigned int[numStudents];
	
	for( unsigned int i = 0 ; i < numStudents; ++i )
		m_offsets[i] = 0;

	m_machines = new VendingMachine*[numVendingMachines];

}

NameServer::~NameServer() {
	delete[] m_offsets;
	delete[] m_machines;
}


void NameServer::VMregister( VendingMachine *vendingmachine ){
	m_printer->print( Printer::NameServer, 'R', m_machineCount );
	m_machines[ m_machineCount++ ] = vendingmachine;
}

VendingMachine* NameServer::getMachine( unsigned int id ){
	unsigned int machineID = (id + m_offsets[id]++) % m_numMachines;

	m_printer->print( Printer::NameServer, 'N', id, machineID );
	return m_machines[ machineID ];
}


VendingMachine** NameServer::getMachineList(){
	return m_machines;
}

void NameServer::main(){
	m_printer->print( Printer::NameServer, 'S' );

	while (true){
		_Accept( ~NameServer ) { break; }
		or _Accept( VMregister ) { }
		//Only accept calls to the machines once all the machines are registered
		or _When( m_machineCount == m_numMachines ) _Accept( getMachine, getMachineList ) { }
	}

	m_printer->print( Printer::NameServer, 'F' );
}
