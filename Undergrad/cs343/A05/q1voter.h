#ifndef _Q1VOTER_H
#define _Q1VOTER_H

#include <uC++.h>
#include <iostream>
#include "MPRNG.h"


_Monitor Printer;
class TallyVotes;


extern MPRNG randGen;

_Task Voter {

	private:
		void main();
		unsigned int m_id;
		TallyVotes *m_voteTallier;
		Printer *m_prt;

  public:

		enum States { Start = 'S', Vote = 'V', Block = 'B', 
									Unblock = 'U', Complete = 'C', Finished = 'F' };

		Voter(unsigned int id, TallyVotes &voteTallier, Printer &prt) : m_id(id), m_voteTallier(&voteTallier), m_prt(&prt) {}

};


#endif
