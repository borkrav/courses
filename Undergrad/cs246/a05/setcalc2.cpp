#include "strset2.h"
#include <vector>
#include <iostream>
#include "help.h"

using namespace std;

bool output = false;

struct set {
	string name;
	strSet data;
};

vector<set> memory;


int findSet(string input){
	
	int index = -1;
	
	if (memory.size() == 0) {
		return index;
	}
	
	for (int i = 0; i < memory.size(); i++){
		if (memory[i].name == input) {
			index = i;
		}
	}
	
	if (index > -1) {
		return index;
	}
	
	return index;
	
}


int main(int argc,char *argv[]){
	
	bool quit = false;
	char com;
	string name;
	string name2;
	string name3;
	string input;
	
	
	if (argc == 2) {
		output = true;
	}
	
	if (output) {
		cout << "Welcome to string set calculator.  Type 'h' for help." <<endl;
		
	}
	
	while (!quit){
		
		
		if (output) {
			cout << "Command: ";
		}
		
		
		cin >> com;
		
		if (com == 'q') {
			
			if (output) {
				cout << "Quitting." << endl;
				
			}
			
			quit = true;
		}
		
		if (com == 'd') {
			
			if (output) {
				cout << "Declare (to be empty).  Give set: ";			
			}
			
			strSet aaa("NULL");
			
			cin >> name;
			set empty;
			empty.name = name;
			empty.data = aaa;
			
			
			if (findSet(name) > -1) {
				cerr << "ERROR: Multiple declaration" << endl;
			}
			else {
				memory.push_back(empty);
			}
			
		}
		
		if (com == 's') {
			
			if (output) {
				cout << "Declare (to be singleton).  Give set element: ";
			}
			
			cin >> name;
			cin >> input;
			set empty;
			if (findSet(name) > -1) {
				cerr << "ERROR: Multiple declaration" << endl;
			}
			else {
				empty.name = name;
				empty.data = empty.data + input;
				memory.push_back(empty);
			}
			
		}
		
		if (com == 'b'){
			
			if (output) {
				cout << "Declare, build set. Give set { elem1 elem2 ... }:" << endl;
			}
			
			
			set empty;
			cin >> name;
			empty.name = name;
			
			if (findSet(name) > -1) {
				cerr << "ERROR: Multiple declaration" << endl;
				
			}
			
			else {
				cin >> input;
				
				if (input != "{") {
					cerr << "ERROR: Bad format" << endl;
				}
				
				
				else {
					
					while (true) {
						cin >> input;
						
						if (input == "}") {
							break;
						}
						
						empty.data = empty.data + input;
					}
					
					
					if (empty.data.SIZE() == 0) {
						strSet aaa("NULL");
						set null;
						null.data = aaa;
						null.name = name;
						memory.push_back(null);
						
					}
					
					else {
						memory.push_back(empty);

					}

				}
				
			}
		}
		
		if (com == 'o') {
			
			
			
			if (output) {
				cout << "Output.  Give set: ";
			}
			
			cin >> name;
			
			
			if (findSet(name) == -1) {
				cerr << "ERROR: No such set" << endl;
			}
			
			else if (!memory[findSet(name)].data.isNull()) {
				memory[findSet(name)].data.output();
			}
					
		}
		
		if (com == 'p') {
			cin >> name;
			cout << name << endl;
		}
		
		if (com == 'h') {
			help();
		}
		
		if (com == '=') {
			
			if (output) {
				cout << "Assign.  Give set1 set2: ";
			}
			
			cin >> name;
			cin >> name2;
			
			if (findSet(name) == -1 || findSet(name2) == -1) {
				cerr << "ERROR: Undeclared" << endl;
			}
			
			else {
				
				memory[findSet(name)].data = memory[findSet(name2)].data;
			}
		}
		
		if (com == '-') {
			
			if (output) {
				cout << "Subtract.  Give set1 set2 set3: ";
			}
			
			cin >> name;
			cin >> name2;
			cin >> name3;
			
			if (findSet(name) == -1 || findSet(name2) == -1 || findSet(name3) == -1) {
				cerr << "ERROR: Undeclared" << endl;
			}
			
			else {
				memory[findSet(name)].data = memory[findSet(name2)].data - memory[findSet(name3)].data;
			}
			
			
		}
		
		if (com == '*') {
			
			if (output) {
				cout << "Intersection.  Give set1 set2 set3: ";
			}
			
			cin >> name;
			cin >> name2;
			cin >> name3;
			
			if (findSet(name) == -1 || findSet(name2) == -1 || findSet(name3) == -1) {
				cerr << "ERROR: Undeclared" << endl;
			}
			
			else {
				
				memory[findSet(name)].data = memory[findSet(name2)].data * memory[findSet(name3)].data;
				
			}
		}
		
		if (com == '+') {
			
			if (output) {
				cout << "Union.  Give set1 set2 set3: ";
			}
			
			cin >> name;
			cin >> name2;
			cin >> name3;
			
			if (findSet(name) == -1 || findSet(name2) == -1 || findSet(name3) == -1) {
				cerr << "ERROR: Undeclared" << endl;
			}
			
			else {
				memory[findSet(name)].data = memory[findSet(name2)].data + memory[findSet(name3)].data;
			}
		}
		
		if (com != 'q' && com != 'b' && com != 's' && com != 'd' && com != 'h' && com != 'p' && com != '+' && com != '=' && com != '-' && com != '*' && com != 'o' && com != 'v') {
			cerr << "ERROR: Ignoring bad command" << endl;
		}
		
		if (com == 'v' && output == false) {
			output = true;
		}
		
		else if (com == 'v' && output == true) {
			output = false;
		}
		
		
		
		
		
	}
	
	
}
