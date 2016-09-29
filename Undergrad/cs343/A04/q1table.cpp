#include "q1table.h"
#include "q1printer.h"
#include "q1philosopher.h"

using namespace std;

uBaseTask *CurrTid;

void Table::pickup(unsigned int id){

	//get table lock
	m_tableLock->P();

		CurrTid = &uThisTask();

		int left = id - 1;
		int right = id + 1;
		if (id == 0) left = m_noOfPhil-1;
		if (id == m_noOfPhil-1) right = 0;

		//if left or right are eating
		if (m_eating[left] || m_eating[right]){

			//gotta wait
			m_prt->print(id, Philosopher::Waiting);

			while (m_eating[left] || m_eating[right]){
				
				//make sure there's no critical section violation
				assert (CurrTid == &uThisTask());	
				//release table lock		
				m_tableLock->V();
				//block on your semaphore
				m_eat[id]->P();
				//get table lock
				m_tableLock->P();
				CurrTid = &uThisTask();

			}
		}

		//set yourself to eating
		m_eating[id] = true;

		//check for critical section violation
		assert (CurrTid == &uThisTask());			

	m_tableLock->V();
	//release table lock


}

void Table::putdown(unsigned int id){

	//get table lock
	m_tableLock->P();

		CurrTid = &uThisTask();

		int left = id - 1;
		int right = id + 1;
		if (id == 0) left = m_noOfPhil-1;
		if (id == m_noOfPhil-1) right = 0;

		//if left or right are eating right now, there is an error
		assert (!(m_eating[left] || m_eating[left]));

		//set yourself to not eating
		m_eating[id] = false;

		//wake up left and right, if they are blocked right now
		if (!m_eat[left]->TryP()) m_eat[left]->V();
		if (!m_eat[right]->TryP()) m_eat[right]->V();

		//check for critical section violation
		assert (CurrTid == &uThisTask());			

	//release table lock
	m_tableLock->V();

}



Table::Table(unsigned int noOfPhil, Printer &prt) {

	m_noOfPhil = noOfPhil;
	m_prt = &prt;

	//table lock is a binary semaphore
	m_tableLock = new uSemaphore(1);
	
	//eating semaphores for each philosopher
	for (int i = 0; i < m_noOfPhil; i++){
		m_eating.push_back(false);
		m_eat.push_back(new uSemaphore(0));
	}

}

Table::~Table(){

	//delete all mutex and synch
	delete m_tableLock;
	
	for (int i = 0; i < m_noOfPhil; i++){
		delete m_eat[i];
	}


}
