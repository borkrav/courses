#include "q1philosopher.h"
#include "q1table.h"
#include "q1printer.h"

using namespace std;

void Philosopher::main(){

	while (true) {

		m_prt->print(m_id, Hungry);

		yield(randGen(0,4));

		m_table->pickup(m_id);

		//assignment description did not specify bite generation for when noodles < 5, so 		//I assumed generate between 1 to what's left on the plate, inclusive
		int bite = 0;
		if (m_noodles < 5) bite = randGen(1,m_noodles);
		else bite = randGen(1,5);
		
		m_prt->print(m_id, Eating, bite, m_noodles-=bite);

		yield(randGen(0,4));;

		m_table->putdown(m_id);

		//philosopher finished eating
		if (m_noodles == 0) break;

		m_prt->print(m_id, Thinking);

		yield(randGen(0,19));

	} 

	m_prt->print(m_id, Finished);

}

