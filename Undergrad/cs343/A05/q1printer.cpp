#include "q1printer.h"

using namespace std;

string tab = "	";

void Printer::print( unsigned int id, Voter::States state ){
	unifiedPrint(id, state, 0, 0);
}
void Printer::print( unsigned int id, Voter::States state, bool vote ){
	unifiedPrint(id, state, vote, 0);
}
void Printer::print( unsigned int id, Voter::States state, unsigned int numBlocked ){
	unifiedPrint(id, state, 0, numBlocked);
}


void Printer::unifiedPrint(unsigned int id, Voter::States state, bool vote, unsigned int numBlocked){

	//if someone finished
	if (state == Voter::Finished){

			//flush
			flush();

			//and print the finish line
			for (int i = 0; i < buffer.size(); i++){
				if (i+1 == buffer.size()) tab = "\n";
				else tab = "	";
				if (i == id) cout << "F " << vote << tab;
				else cout << "..." << tab;				
			}
	}

	//if buffer is empty
	else if (buffer[id].state == ""){
		
		//write to the buffer
		buffer[id].state = state;
		buffer[id].vote = vote;
		buffer[id].numBlocked = numBlocked;

	}

	//if buffer is not empty
	else if (buffer[id].state != "") {
		
		//flush
		flush();

		//and write to the buffer
		buffer[id].state = state;
		buffer[id].vote = vote;
		buffer[id].numBlocked = numBlocked;

	}	

}


void Printer::flush(){
	
	for (int i = 0; i < buffer.size(); i++){

		bool last = true;

		//if this entry is the last in the row
		if (!(i+1 == buffer.size())){
			for (int j = i+1; j < buffer.size(); j++){
				if (!(buffer[j].state == "")) last = false; 
			}
		}

		//switch the tab to be a new line
		if (last) tab = "\n";
		else tab = "	";

		//print the appropriate data
		if (buffer[i].state == ""){
			cout << tab;
		}

		else if (buffer[i].state == "S" || buffer[i].state == "C"){
			cout << buffer[i].state << tab;
		}

		else if (buffer[i].state == "V"){
			cout << buffer[i].state << " " << buffer[i].vote << tab;
		}

		else if (buffer[i].state == "B" || buffer[i].state == "U"){
			cout << buffer[i].state << " " << buffer[i].numBlocked << tab;
		}

		buffer[i].state = "";

		//if this entry is the last in the row, break out of the loop
		if (last) break;
	}
	
	

}


Printer::Printer( unsigned int voters ){

	m_voters = voters;
	buffer = vector<info>(voters);

	//set up the default empty buffer
	for (int i = 0; i < voters; i++){
		buffer[i] = info{"", 0, 0};
	}

	//print the header
	for (int i = 0; i < voters-1; i++){
		cout << "Voter" << i << "	";
	}
	cout << "Voter" << voters-1 <<endl;


	for (int i = 0; i < voters-1; i++){
		cout << "=======" << "	";
	}
	cout << "=======" << endl;

}

Printer::~Printer(){
	//print the footer on destruct
	cout << "=================" << endl;
	cout << "All tours started" << endl;

}
