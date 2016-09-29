#include "printer.h"

using namespace std;

string tab = "	";

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, 
								 unsigned int numCouriers){

	m_changed = false;
	m_numStudents = numStudents;
	m_numVendingMachines = numVendingMachines;
	m_numCouriers = numCouriers;

	buffer = vector<info>(5 + numStudents + numVendingMachines + numCouriers);

	//set up the default empty buffer
	for (int i = 0; i < buffer.size(); i++){
		buffer[i] = info{0, ' ', 0, 0, 0};
	}

	//print the header
	cout << "Parent\tWATOff\tNames\tTruck\tPlant\t";

	for (int i = 0; i < numStudents; i++)
		cout << "Stud" << i << tab;
	for (int i = 0; i < numVendingMachines; i++)
		cout << "Mach" << i << tab;
	for (int i = 0; i < numCouriers; i++)
		cout << "Cour" << i << tab;

	cout << endl;

	for (int i = 0; i < buffer.size()-1; i++){
		cout << "*******\t";
	}
	cout << "*******" << endl;

}

Printer::~Printer(){
	//print the footer on destruct
	cout << "***********************" << endl;
}

void Printer::print( Kind kind, char state ){
	unifiedPrint(kind, 0, state, 0, 0, 1);
}
void Printer::print( Kind kind, char state, int value1 ){
	unifiedPrint(kind, 0, state, value1, 0, 2);
}
void Printer::print( Kind kind, char state, int value1, int value2 ){
	unifiedPrint(kind, 0, state, value1, value2, 3);
}
void Printer::print( Kind kind, unsigned int lid, char state ){
	unifiedPrint(kind, lid, state, 0, 0, 1);
}
void Printer::print( Kind kind, unsigned int lid, char state, int value1 ){
	unifiedPrint(kind, lid, state, value1, 0, 2);
}
void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ){
	unifiedPrint(kind, lid, state, value1, value2, 3);
}

int Printer::getIndex(Kind kind, unsigned int lid){

	switch (kind){
		case Student:
			return 5+lid;
		case Vending:
			return 5+m_numStudents+lid;
		case Courier:
			return 5+m_numStudents+m_numVendingMachines+lid;
		default:
			return kind;
	}

}

void Printer::unifiedPrint(Kind kind, unsigned int lid, char state, int value1, int value2, int format ){


	int index = getIndex(kind, lid);

	assert (index < buffer.size())

	//if someone finished
	if (state == 'F'){

			//flush
			flush();

			//and print the finish line
			for (int i = 0; i < buffer.size()-1; i++){
				if (i == index) cout << "F" << tab;
				else cout << "..." << tab;				
			}
			cout << ((index==buffer.size())? "F": "...") << endl;
	}




	//if buffer is empty
	else if (buffer[index].format == 0){
		

		//write to the buffer
		buffer[index].lid = lid;
		buffer[index].state = state;
		buffer[index].value1 = value1;
		buffer[index].value2 = value2;
		buffer[index].format = format;

		m_changed = true;

	}

	//if buffer is not empty
	else if (buffer[index].format != 0) {
		
		//flush
		flush();

		//and write to the buffer
		buffer[index].lid = lid;
		buffer[index].state = state;
		buffer[index].value1 = value1;
		buffer[index].value2 = value2;
		buffer[index].format = format;

		m_changed = true;

	}	

}

void Printer::flush(){
	if( !m_changed ) return;

	for (int i = 0; i < buffer.size(); i++){

		//bool last = true;

		//if this entry is the last in the row
		//if (!(i+1 == buffer.size())){
		//	for (int j = i+1; j < buffer.size(); j++){
		//		if (!(buffer[j].format == 0)) last = false; 
		//	}
		//}

		//switch the tab to be a new line
		//if (last) tab = "\n";
		//else tab = "	";


		switch (buffer[i].format) {
			case 0:
				cout << tab;
				break;
			case 1:
				cout << buffer[i].state << tab;
				break;
			case 2:
				cout << buffer[i].state << buffer[i].value1 << tab;
				break;
			case 3:
				cout << buffer[i].state << buffer[i].value1 << "," << buffer[i].value2 << tab;
				break;
		}

		buffer[i].format = 0;

		//if this entry is the last in the row, break out of the loop
		//if (last) break;
	}
	
	cout << endl;
	m_changed = false;
}
