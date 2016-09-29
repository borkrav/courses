#include "q1tallyVotes.h"
#include "q1voter.h"
#include "q1printer.h"

using namespace std;

bool TallyVotes::vote( unsigned int id, bool ballot ){

	m_voters++;
	//print and save vote to results array
	m_prt->print(id, Voter::Vote, ballot);
	m_results[m_voters-1] = ballot;

	//if I'm not the last voter in the group, wait
	if (m_voters != m_group) wait(id);

	else {
		//if I'm the last voter in the group, get the result and print stuff
		m_result = getResult();

		m_prt->print(id, Voter::Complete);
		m_prt->print(id, Voter::Finished, m_result);

		//wake up the waiting voters in LIFO order
		for (int i = 0; i < m_group-1; i++) m_sleepers[i]->signal();

		m_voters = 0;		

	}

	return m_result;

}

void TallyVotes::wait(unsigned int id){

	m_ballots++;

	//print message and wait on the sleeper array
	m_prt->print(id, Voter::Block, m_ballots);
	m_sleepers[m_ballots-1]->wait();

	//print finishing messages
	m_ballots--;
	m_prt->print(id, Voter::Unblock, m_ballots);
	m_prt->print(id, Voter::Finished, m_result);

}




TallyVotes::TallyVotes( unsigned int group, Printer &prt ){

	m_group = group;
	m_prt = &prt;
	m_voters = 0;
	m_ballots = 0;
	m_results = vector<bool>(m_group);

	for (int i = 0; i < group-1; i++){
		m_sleepers.push_back(new uCondition());
	}
	

}

TallyVotes::~TallyVotes(){

	for (int i = 0; i < m_group-1; i++){
		delete m_sleepers[i];
	}


}
