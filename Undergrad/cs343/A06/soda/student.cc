#include "student.h"
#include "vendingMachine.h"

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, 
		unsigned int id, unsigned int maxPurchases ) 

	: m_printer(&prt), m_server(&nameServer), m_office(&cardOffice), 
		m_id(id), m_purchases( number_generator(1, maxPurchases) ) { }


//---
WATCard* Student::getNewCard() {
	WATCard* result;
	
	try {
		
		result = m_office->create( m_id, 5 )();

	} catch( WATCardOffice::Lost ) {
		result = getNewCard();
	}

	return result;

}


void Student::main() {
	unsigned int flavour = number_generator( 3 );
	m_printer->print( Printer::Student, m_id, 'S', flavour, m_purchases );


	WATCard* card = getNewCard();

	VendingMachine* machine = m_server->getMachine( m_id );
	m_printer->print( Printer::Student, m_id, 'V', machine->getId() );
	for(; m_purchases > 0; --m_purchases ) {
		//Wait for thirst
		yield( number_generator( 1, 10 ) );			
		
		//Keep trying to buy while things go wrong
		bool has_not_bought = true;
		while( has_not_bought ) {

			//Perform a buy and switch on it
			switch( machine->buy( (VendingMachine::Flavours)flavour, *card ) ) {
				//I'm out of money
				case VendingMachine::FUNDS:
					try {
						card = m_office->transfer( m_id, 5 + machine->cost(), card )();
					} catch ( WATCardOffice::Lost ) {
						m_printer->print( Printer::Student, m_id, 'L' );
						card = getNewCard();
					}
					break;
				//Machine is out of stock
				case VendingMachine::STOCK:
					machine = m_server->getMachine( m_id );
					m_printer->print( Printer::Student, m_id, 'V', machine->getId() );	
					break;
				//Purchase successful
				case VendingMachine::BUY:
					has_not_bought = false;
					m_printer->print( Printer::Student, m_id, 'B', card->getBalance() );
					break;					
			}
	
		}

	}

	m_printer->print( Printer::Student, m_id, 'F' );
	delete card;
}
