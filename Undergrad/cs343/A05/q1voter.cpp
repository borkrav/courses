#include "q1voter.h"
#include "q1printer.h"
#include "q1tallyVotes.h"

using namespace std;

void Voter::main(){

	//print starting message
	m_prt->print(m_id, Start);

	
	yield(randGen(0,19));

	//generate vote and vote
	bool vote = (bool) randGen(0,1);
	bool result = m_voteTallier->vote(m_id, vote);

	//note, the finish message is printed inside vote, so I'm not actually using the result here

}
