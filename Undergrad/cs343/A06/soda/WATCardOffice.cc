#include "WATCardOffice.h"
#include "bank.h"

WATCardOffice::Courier::Courier( Printer &printer, WATCardOffice *office, Bank &bank, unsigned int id ) 
	: m_printer( &printer), m_office( office ), m_bank( &bank ), m_id(id) {
 }

void WATCardOffice::Courier::main() {

	Job *current_job;

	m_printer->print(Printer::Courier, m_id, 'S');
	while( true ) {
		//Get a job
		current_job = m_office->requestWork();

		//Leave if the job does not exist
		if( current_job == NULL ) break;
		m_printer->print( Printer::WATCardOffice, m_id, 'W' );

		//Randomly lose a card with a chance of 1:6
		if( number_generator( 1, 6 ) == 6 ) {
			//Clean the card we're losing			
			delete current_job->card;
			current_job->result.exception( new Lost );

		} else {
	
			//Withdraw money from the bank
			m_printer->print(Printer::Courier, m_id, 't', current_job->id, current_job->amount);
			m_bank->withdraw( current_job->id, current_job->amount );

			//Put the money into the card
			current_job->card->deposit( current_job->amount );
			m_printer->print(Printer::Courier, m_id, 'T', current_job->id, current_job->amount);

			//Return the card to the student
			current_job->result.delivery( current_job->card );
		}

		delete current_job;
	}

	m_printer->print(Printer::Courier, m_id, 'F');

}


WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
	: m_printer( &prt ), m_bank( &bank ) {

	for( unsigned int i = 0; i < numCouriers; ++i )
		m_couriers.push_back( new Courier( prt, this, bank, i ) );	 
}

WATCardOffice::~WATCardOffice() {
	//Push a terminating job onto the queue for each courier
	for( unsigned int i = 0; i < m_couriers.size(); ++i) {
		job_mutex.acquire();
			m_jobs.push( NULL );
		job_mutex.release();
	}
	
	while( !m_jobs.empty() ) { _Accept( requestWork ); }

	//Wait for all the couriers to finish
	for( unsigned int i = 0; i < m_couriers.size(); ++i)
		delete m_couriers[i];	

}

FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	WATCard* new_card = new WATCard();
	Job* create_card_job = new Job( sid, amount, new_card );

	job_mutex.acquire();
		m_jobs.push( create_card_job );
	job_mutex.release();

	m_printer->print( Printer::WATCardOffice, 'C', sid, amount );
	return create_card_job->result;
}

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ){
	Job* get_money_job = new Job( sid, amount, card );

	job_mutex.acquire();
		m_jobs.push( get_money_job );
	job_mutex.release();
	

	m_printer->print( Printer::WATCardOffice, 'T', sid, amount );
	return get_money_job->result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
	Job* my_job;

	job_mutex.acquire();
		my_job = m_jobs.front();
		m_jobs.pop();
	job_mutex.release();

	return my_job;
}

void WATCardOffice::main() {
	m_printer->print( Printer::WATCardOffice, 'S' ); 
	
	while( true ) {
		
		_Accept( ~WATCardOffice ) { break; } or
		_When( !m_jobs.empty() ) _Accept( requestWork ) { } or 
		_Accept( create, transfer );
	}

	m_printer->print( Printer::WATCardOffice, 'F' ); 
}
