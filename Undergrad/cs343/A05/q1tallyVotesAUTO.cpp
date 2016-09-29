#include "q1tallyVotes.h"
#include "q1voter.h"
#include "q1printer.h"


using namespace std;

bool TallyVotes::vote( unsigned int id, bool ballot ){

	m_voters++;

	//print the vote and save thew vote in results array
	m_prt->print(id, Voter::Vote, ballot);
	m_results[m_voters-1] = ballot;

	//if I'm not last, call wait function
	if (m_voters != m_group) wait(id);

	else {
		//I am last, set voteIsDone to true, get result, print stuff and exit
		voteIsDone = true;
		m_result = getResult();

		m_prt->print(id, Voter::Complete);
		m_prt->print(id, Voter::Finished, m_result);
	}


	m_voters = 0;

	RETURN(m_result);


}

void TallyVotes::wait(unsigned int id){

	m_ballots++;

	voteIsDone = false;

	m_prt->print(id, Voter::Block, m_ballots);

	//wait until the last voter sets voteISDone to true
	WAITUNTIL(voteIsDone,,)

	
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

	

}

TallyVotes::~TallyVotes(){


}
