#include "bottlingPlant.h"
#include "truck.h"
#include "nameServer.h"


BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments ) 
	: m_printer( &prt ), m_maxShipped( maxShippedPerFlavour ), m_delay( timeBetweenShipments ),
		m_finished( false ){

	m_truck = new Truck( prt, nameServer, *this, numVendingMachines, maxStockPerFlavour );
	for( int i = 0; i < NUMBER_OF_FLAVOURS; ++i )
		m_inventory[i] = 0;
}

BottlingPlant::~BottlingPlant() { 
	m_finished = true;
	_Accept(getShipment);
	
	delete m_truck;
}

bool BottlingPlant::getShipment( unsigned int cargo[] ){
	if( m_finished ) return true;

	//Move inventory into cargo
	for( unsigned int i = 0; i < NUMBER_OF_FLAVOURS; ++i) {
		cargo[i] = m_inventory[i];
	}
	m_printer->print( Printer::BottlingPlant, 'P' );

	return false;
}


void BottlingPlant::main(){
	m_printer->print( Printer::BottlingPlant, 'S' );
	while (true){

		_Accept( ~BottlingPlant ) { break; }
		or _Accept(getShipment);

		yield(m_delay);

		unsigned int numGenerated = 0;
		for( unsigned int i = 0; i < NUMBER_OF_FLAVOURS; ++i) {
			numGenerated += (m_inventory[i] = number_generator(0, m_maxShipped) );
		}
		m_printer->print( Printer::BottlingPlant, 'G', numGenerated );

	}
	
	m_printer->print( Printer::BottlingPlant, 'F' );
}
