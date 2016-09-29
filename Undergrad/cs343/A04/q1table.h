#ifndef _Q1TABLE_H
#define _Q1TABLE_H

#include <vector>
#include <iostream>
#include <uSemaphore.h>

_Monitor Printer;

class Table {
	private:
		unsigned int m_noOfPhil;
		Printer *m_prt;
		uSemaphore *m_tableLock;
		std::vector<uSemaphore*> m_eat;
		std::vector<bool> m_eating;

  public:
    Table(unsigned int noOfPhil, Printer &prt);
		~Table();
    void pickup(unsigned int id);
    void putdown(unsigned int id);
}; // Table

#endif
