#ifndef __BANK__
#define __BANK__

#include "common.h"

_Monitor Bank {

	uCondition *m_wait_for_deposit;
	unsigned int *m_accounts;

  public:
    Bank( unsigned int numStudents );
		~Bank();
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};


#endif
