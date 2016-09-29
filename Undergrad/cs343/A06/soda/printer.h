#ifndef __PRINTER__
#define __PRINTER__

#include "common.h"

typedef struct {
	unsigned int lid;
	char state;
	int value1;
	int value2;
	int format;
} info;



_Monitor Printer {
  public:
    enum Kind { Parent, WATCardOffice, NameServer, 
								Truck, BottlingPlant, Student, Vending, Courier };

    Printer( unsigned int numStudents, unsigned int numVendingMachines, 
							unsigned int numCouriers );

		~Printer();
		
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );


	private:
	  	bool m_changed;
		unsigned int m_numStudents;
		unsigned int m_numVendingMachines;
		unsigned int m_numCouriers;
		std::vector<info> buffer;
		void flush();
		void unifiedPrint(Kind kind, unsigned int lid, char state, int value1, 
											int value2, int format );
		int getIndex(Kind kind, unsigned int lid);

};



#endif
