#include "q1printer.h"

using namespace std;

void Printer::print(unsigned int id, Philosopher::States state){

	print(id, state, 0, 0);

}

void Printer::print(unsigned int id, Philosopher::States state, unsigned int bite, unsigned int noodles){

	//if someone finished, flush and print the finish line
	if (state == Philosopher::Finished){

			flush();

			for (int i = 0; i < buffer.size(); i++){
				if (i == id) cout << "F	";
				else cout << "...	";				
			}
			cout << endl;
	}

	//if buffer is empty
	else if (buffer[id].state == ""){
		
		//write to the buffer

		buffer[id].state = state;
		buffer[id].bite = bite;
		buffer[id].noodles = noodles;


	}

	//if buffer is not empty
	else if (buffer[id].state != "") {
		
		//flush
		flush();

		//and write to the buffer
		buffer[id].state = state;
		buffer[id].bite = bite;
		buffer[id].noodles = noodles;

	}	

}


void Printer::flush(){


	string tab = "	";
	
	for (int i = 0; i < buffer.size(); i++){

		//if there's nothing in the buffer slot, print empty space
		if (buffer[i].state == ""){
			cout << "" << tab;
		}

		//if state is waiting
		else if (buffer[i].state == "W"){

			int left = i;
			int right = i + 1;
			if (i == m_noOfPhil-1) right = 0;
			cout << buffer[i].state << left << "," << right << tab;

		}

		//if state is eating
		else if (buffer[i].state == "E"){
			cout << buffer[i].state << buffer[i].bite << "," << buffer[i].noodles << tab;
		}

		//if state is thinking or hungry
		else {
			cout << buffer[i].state << tab;
		}

		buffer[i].state = "";
	}
	
	cout << endl;

}


Printer::Printer(unsigned int NoOfPhil){

	m_noOfPhil = NoOfPhil;
	buffer = vector<info>(NoOfPhil);

	//set up the default empty buffer
	for (int i = 0; i < NoOfPhil; i++){

		buffer[i] = info{"", 0, 0};

	}

	//print the header
	for (int i = 0; i < NoOfPhil; i++){
		cout << "Phil" << i << "	";
	}
	cout << endl;

	for (int i = 0; i < NoOfPhil; i++){
		cout << "******" << "	";
	}
	cout << endl;

}
