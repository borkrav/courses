#include "q1tallyVotes.h"
#include "q1voter.h"
#include "q1printer.h"

using namespace std;

void TallyVotes::main(){

	//this yied ensures that the outputs match -> all the voters tasks start 
	//before the first task
	yield();


	while (true){

		//at any time, accept the destructor or accept votes
		_Accept( ~TallyVotes )
			break;
		or _Accept(vote);

		//if there are enough tasks to fill a group
		if (m_arrivers.size() == m_group){
				
				//get the result
				m_result = getResult();				

				//print the complete message under the last task to enter
				m_prt->print(m_arrivers[m_group-1], Voter::Complete);
				
				//for every arriver in the current group, print unblock and finish messages 				//in FIFO order and signal block to allow the task to end
				for (int i = 0; i < m_group; i++) {
					m_prt->print(m_arrivers[i], Voter::Unblock, m_group-i-1);
					m_prt->print(m_arrivers[i], Voter::Finished, m_result);
					m_sleepers.signalBlock();
				}

				//clear both arrays
				m_arrivers.clear();	
				m_results.clear();
		}

	}


}


bool TallyVotes::vote( unsigned int id, bool ballot ){

	//put myself on the arriver array
	m_arrivers.push_back(id);
	//print vote and save onto results array
	m_prt->print(id, Voter::Vote, ballot);
	m_results.push_back(ballot);
	//wait on the sleeper condition
	m_prt->print(id, Voter::Block, (unsigned int)m_arrivers.size());
	m_sleepers.wait();

	return m_result;

}


TallyVotes::TallyVotes( unsigned int group, Printer &prt ){

	m_group = group;
	m_prt = &prt;
	m_voters = group;
	
}

TallyVotes::~TallyVotes(){

}
