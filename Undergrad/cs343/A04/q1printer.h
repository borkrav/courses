#ifndef _Q1PRINTER_H
#define _Q1PRINTER_H

#include <uC++.h>
#include "q1philosopher.h"
#include <vector>
#include <utility>

typedef struct {
	std::string state;
	unsigned int bite;
	unsigned int noodles;
} info;


_Monitor Printer {

	private:
		unsigned int m_noOfPhil;
		std::vector<info> buffer;
		void flush();


  public:
    Printer(unsigned int NoOfPhil);
    void print(unsigned int id, Philosopher::States state);
    void print(unsigned int id, Philosopher::States state, unsigned int bite, unsigned int noodles);

}; // Printer

#endif
