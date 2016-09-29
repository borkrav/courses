#include "q1tallyVotes.h"
#include "q1voter.h"
#include "q1printer.h"

using namespace std;

bool TallyVotes::vote( unsigned int id, bool ballot ){


	//this allows the group size voters in, blocks everyone after
	entry->P();

	mutex.acquire();

	m_voters++;

	m_prt->print(id, Voter::Vote, ballot);

	//set the result array with the ballot
	m_results[m_voters-1] = ballot;


	if (m_voters != m_group) {
		//if I'm not the last voter
		m_ballots++;

		//print that I'm blocked and wait on a sleeper array
		if (m_ballots < m_group) {
			m_prt->print(id, Voter::Block, m_ballots);
			m_sleepers[m_ballots-1]->wait(mutex);
		}

		//print that i'm done once I'm unblocked
		m_ballots--;
		m_prt->print(id, Voter::Unblock, m_ballots);
		m_prt->print(id, Voter::Finished, m_result);
		m_voters--;	


	}

	else {
		//if I'm the last voter

		//get the result
		m_result = getResult();

		//print my finishing messages
		m_prt->print(id, Voter::Complete);
		m_prt->print(id, Voter::Finished, m_result);

		//wake the sleeper array in LIFO order
		for (int i = m_group-2; i >= 0; i--) {
			m_sleepers[i]->signal();
		}

		m_voters--;

	}

	//if the vote is finished, wake up anyone that arrived during the vote
	if (m_voters == 0){
		entry->V(m_group);
	}


	mutex.release();

	return m_result;

}




TallyVotes::TallyVotes( unsigned int group, Printer &prt ){

	m_group = group;
	m_prt = &prt;
	m_voters = 0;
	m_ballots = 0;
	m_results = vector<bool>(m_group);

	for (int i = 0; i < group-1; i++){
		m_sleepers.push_back(new uCondLock());
	}

	entry = new uSemaphore(group);
	
}

TallyVotes::~TallyVotes(){

	for (int i = 0; i < m_group-1; i++){
		delete m_sleepers[i];
	}

	delete entry;


}
