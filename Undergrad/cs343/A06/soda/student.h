#ifndef __STUDENT__
#define __STUDENT__

#include "common.h"
#include "nameServer.h"
#include "WATCardOffice.h"

_Task Student {
		Printer* m_printer;
		NameServer* m_server;
		WATCardOffice* m_office;

		unsigned int m_id, m_purchases;
	
		WATCard* getNewCard();

    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
		~Student() { }
};

#endif
