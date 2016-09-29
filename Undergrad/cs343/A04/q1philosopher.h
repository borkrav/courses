#ifndef _Q1PHILISOPHER_H
#define _Q1PHILISOPHER_H

#include <uC++.h>
#include <iostream>
#include "MPRNG.h"

_Monitor Printer;
class Table;

extern MPRNG randGen;

_Task Philosopher {

	private:
		void main();
		unsigned int m_id;
		unsigned int m_noodles;
		Table *m_table;
		Printer *m_prt;


  public:
    enum States {Thinking = 'T', Hungry = 'H', Eating ='E', Waiting = 'W', Finished = 'F'};
    Philosopher(unsigned int id, unsigned int noodles, Table &table, Printer &prt) :
								m_id(id), m_noodles(noodles), m_table(&table), m_prt(&prt) {};

}; // Philosopher

#endif
