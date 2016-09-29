#include "bank.h"

Bank::Bank( unsigned int numStudents ) {
	m_wait_for_deposit = new uCondition[numStudents];
	m_accounts = new unsigned int[numStudents];

	//Zero out each account
	for(unsigned int i = 0; i < numStudents; ++i)
		m_accounts[i] = 0;
}

Bank::~Bank() {
	delete[] m_wait_for_deposit;
	delete[] m_accounts;
}


void Bank::deposit( unsigned int id, unsigned int amount ) {

	m_accounts[id] += amount;
	if( !m_wait_for_deposit[id].empty() ) m_wait_for_deposit[id].signal();

	
}
void Bank::withdraw( unsigned int id, unsigned int amount ) {
	while( m_accounts[id] < amount ) {
		m_wait_for_deposit[id].wait();
	}

	m_accounts[id] -= amount;
}
