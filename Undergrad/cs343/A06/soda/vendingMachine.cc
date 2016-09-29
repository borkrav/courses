#include "vendingMachine.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, 
										unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour )
	: m_prt(&prt), m_nameServer(&nameServer), m_id(id), m_sodaCost(sodaCost), 
		m_maxStockPerFlavour(maxStockPerFlavour), m_restocking(false) {

	m_stock = new unsigned int[ NUMBER_OF_FLAVOURS ];

	for (int i = 0; i<NUMBER_OF_FLAVOURS; i++){
		m_stock[i] = 0;
	}

}

VendingMachine::~VendingMachine() {
	delete[] m_stock;
}

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ){
	if( card.getBalance() < m_sodaCost ) return FUNDS;
	if( m_stock[ flavour ] == 0 ) return STOCK;

	--m_stock[ flavour ];
	card.withdraw( m_sodaCost );

	m_prt->print(Printer::Vending, m_id, 'B', flavour, m_stock[ flavour ]);

	return BUY;
}

unsigned int* VendingMachine::inventory(){
	m_restocking = true;
	m_prt->print(Printer::Vending, m_id, 'r');
	return m_stock;
}

void VendingMachine::restocked(){
	m_restocking = false;
	m_prt->print(Printer::Vending, m_id, 'R');
}

unsigned int VendingMachine::cost(){
	return m_sodaCost;
}

unsigned int VendingMachine::getId(){
	return m_id;
}

void VendingMachine::main(){

	m_prt->print(Printer::Vending, m_id, 'S' , m_sodaCost);

	m_nameServer->VMregister( (VendingMachine*)this );	

	while (true){
		_Accept( ~VendingMachine ) break;
			or _Accept( inventory, restocked );
			or _When(!m_restocking) _Accept( buy );
	}

	m_prt->print(Printer::Vending, m_id, 'F');

}
