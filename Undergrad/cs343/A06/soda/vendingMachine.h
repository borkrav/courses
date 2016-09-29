#ifndef __VENDINGMACHINE__
#define __VENDINGMACHINE__

#include "common.h"
#include "nameServer.h"
#include "WATCard.h"

_Task VendingMachine {
    void main();
		Printer* m_prt;
		NameServer* m_nameServer;
		unsigned int m_id;
		unsigned int m_sodaCost;
		unsigned int m_maxStockPerFlavour;
		unsigned int* m_stock;

		bool m_restocking;
 
  public:
    enum Flavours { BLUES, CLASSICAL, ROCK, JAZZ }; 
    enum Status { BUY, STOCK, FUNDS };
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );

		~VendingMachine();
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif
