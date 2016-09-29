#ifndef _Q1PRINTER_H
#define _Q1PRINTER_H

#include <uC++.h>
#include "q1voter.h"
#include <vector>


typedef struct {
	std::string state;
	bool vote;
	unsigned int numBlocked;
} info;



_Monitor Printer {

	private:
		unsigned int m_voters;
		std::vector<info> buffer;
		void flush(); 
		void unifiedPrint(unsigned int id, Voter::States state, bool vote, unsigned int numBlocked);


	public:
		Printer( unsigned int voters );
		~Printer();
		void print( unsigned int id, Voter::States state );
		void print( unsigned int id, Voter::States state, bool vote );
		void print( unsigned int id, Voter::States state, unsigned int numBlocked );
};

#endif
