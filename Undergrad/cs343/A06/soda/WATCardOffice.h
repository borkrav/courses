#ifndef __WATCARDOFFICE__
#define __WATCARDOFFICE__

#include "common.h"
#include "WATCard.h"
#include <queue>

extern MPRNG number_generator;

_Monitor Bank;

_Task WATCardOffice {
    struct Job {				// marshalled arguments and return future
			unsigned int id, amount;
			WATCard *card;
				
			FWATCard result;			// return future
			Job( unsigned int i, unsigned int a, WATCard* c ) : id(i), amount(a), card(c) {}
		};

		_Task Courier {
				Printer* m_printer;
				WATCardOffice *m_office;
				Bank* m_bank;

				unsigned int m_id;

				void main();
			public:
				Courier( Printer &p, WATCardOffice *o, Bank &b, unsigned int id );
				~Courier() { }	
		};


		//--------------
		Printer *m_printer;
		Bank *m_bank;

		uLock job_mutex;

		std::queue< Job* > m_jobs;
		std::vector<Courier*> m_couriers;

    void main();

		std::string m_word;

  public:
    _Event Lost {};

    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
		~WATCardOffice();

    FWATCard create( unsigned int sid, unsigned int amount );
    FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif
