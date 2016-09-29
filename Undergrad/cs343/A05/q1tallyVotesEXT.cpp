#include "q1tallyVotes.h"
#include "q1voter.h"
#include "q1printer.h"

using namespace std;

bool TallyVotes::vote( unsigned int id, bool ballot ){
	
	m_voters++;
	//print vote and save vote in results array
	m_prt->print(id, Voter::Vote, ballot);
	m_results[m_voters-1] = ballot;

	//if I'm not last, wait
	if (m_voters != m_group) wait(id);

	else {
		//if I'm last calculate the result, print stuff and exit
		m_result = getResult();

		m_prt->print(id, Voter::Complete);
		m_prt->print(id, Voter::Finished, m_result);

	}

	m_voters--;

	return m_result;

}

void TallyVotes::wait(unsigned int id){

	m_ballots++;

	m_prt->print(id, Voter::Block, m_ballots);
	_Accept(vote);

	m_ballots--;

	//print stuff and exit
	m_prt->print(id, Voter::Unblock, m_ballots);
	m_prt->print(id, Voter::Finished, m_result);


}




TallyVotes::TallyVotes( unsigned int group, Printer &prt ){

	m_group = group;
	m_prt = &prt;
	m_voters = 0;
	m_ballots = 0;
	m_results = vector<bool>(m_group);
	

}

TallyVotes::~TallyVotes(){

}
