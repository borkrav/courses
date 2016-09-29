#ifndef __PARENT__
#define __PARENT__

#include "common.h"
#include "bank.h"

extern MPRNG number_generator;

_Task Parent {
		Printer* m_printer;
		Bank* m_bank;

		unsigned int m_nStudents, m_delay;

    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif
