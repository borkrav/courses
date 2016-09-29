#include "truck.h"
#include "bottlingPlant.h"
#include "vendingMachine.h"
#include "nameServer.h"

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour )
	: m_printer(&prt), m_plant(&plant), 
		m_numMachines(numVendingMachines), m_maxStock(maxStockPerFlavour) { 

		m_machines = nameServer.getMachineList();
		m_cargo = new unsigned int[ NUMBER_OF_FLAVOURS ];
		for( unsigned int i = 0; i < NUMBER_OF_FLAVOURS; ++i )
			m_cargo[i] = 0;
}


Truck::~Truck(){
	delete[] m_cargo;
}


int Truck::size() {
	int s = 0;
	for( unsigned int i = 0; i < NUMBER_OF_FLAVOURS; ++i )
		s += m_cargo[i];

	return s;
}

void Truck::main(){
	m_printer->print( Printer::Truck, 'S' );


	while( true ) {
		yield( number_generator( 1, 10 ) );

		if( m_plant->getShipment( m_cargo ) ) { break; }
		m_printer->print( Printer::Truck, 'P', size() );
		
		unsigned int* vending_stock;
		for( unsigned int i = 0; size() > 0 && i < m_numMachines; ++i ) {
			m_printer->print( Printer::Truck, 'd', i, size() );

			vending_stock = m_machines[i]->inventory();
		
			unsigned int unfilled = 0;
			for( unsigned int j = 0; j < NUMBER_OF_FLAVOURS; ++j )
				if( vending_stock[j] < m_maxStock ) {
					int bottles = m_maxStock - vending_stock[j];
					bottles = ( bottles > m_cargo[j] ) ? m_cargo[j] : bottles;
										

					vending_stock[j] += bottles;
					m_cargo[j] -= bottles;

					unfilled += m_maxStock - vending_stock[j];
				}

			m_printer->print( Printer::Truck, 'U', i, unfilled );
			m_printer->print( Printer::Truck, 'D', i, size() );

			m_machines[i]->restocked();
		}
	}
	m_printer->print( Printer::Truck, 'F' );
}
