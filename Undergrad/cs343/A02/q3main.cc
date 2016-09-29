#include <uC++.h>
#include "q3searcher.h"
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;


/* A helper function which prints the results
*	INPUTS
* 		list<Searcher::Node> &input - the list which we are printing
*	OUTPUT
*			void
*/
void outputResult(list<Searcher::Node> &input){

	list<Searcher::Node>::iterator iter;
	for(iter = input.begin(); iter != input.end(); iter++){
		//sets the tab width
		cout.width(4);		
		//prints the key and value, right justifying the key
		cout << right << iter->key << " " << iter->value << endl;
	}

}

/* A helper function which parses the multiset file
*	INPUTS
* 		list<Searcher::Node> &input - the list which we are filling with information
*			string fileName - the name of the file which we open
*	OUTPUT
*			void
*/
void readMultiset(list<Searcher::Node> &input, string fileName){

		string inputLine;
		ifstream myfile;
		
		//if the file can't be opened, exit
		if (access(fileName.c_str(), F_OK) != 0 || access(fileName.c_str(), R_OK) != 0){
			cerr << "Error! Could not open multiset file \"" << fileName << "\"" << endl;	
			exit(0);
		}
		
		myfile.open( fileName.c_str() );

		//reads the file line by line
		while ( getline(myfile, inputLine ) ) {
			int i;
			//scan over the line until we get to the last digit in that line, this will be the key
			for (i = 0; isdigit(inputLine[i]) != 0; i++){
			}

			//push back the key and the value, dividing the line by the index of the last digit
			input.push_back(
					Searcher::Node(atoi(inputLine.substr(0,i).c_str()), 
												inputLine.substr(i,inputLine.length()-i)));
		}

		myfile.close();

}

/* A helper function which parses the key file
*	INPUTS
* 		list<Searcher::Node> &input - the list which we are filling with information
*			string fileName - the name of the file which we open
*	OUTPUT
*			void
*/
void readKeys(list<int> &input, string fileName){

		string inputLine;
		ifstream myfile;
		
		//if the file can't be opened, exit
		if (access(fileName.c_str(), F_OK) != 0 || access(fileName.c_str(), R_OK) != 0){
			cerr << "Error! Could not open search-key file \"" << fileName <<"\""<< endl;	
			exit(0);
		}
		
		myfile.open( fileName.c_str() );

		string value;

		//parses out the newlines
		while ( getline(myfile, inputLine) )	{


			stringstream iss(inputLine);
			//parses out the white space
			while (iss >> value){
				//pushes the key onto the input list
				input.push_back(atoi(value.c_str()));
			}

		}

		myfile.close();

}

/* A helper function searches for a key in the multiset list
*	INPUTS
* 		list<Searcher::Node> &multiset - the list which the search is performed on
*			int value - the key we're searching for
*	OUTPUT
*			void
*/
void search(list<Searcher::Node> &multiset, int value){

				list<Searcher::Node>::iterator multisetIter = multiset.begin();				
				list<Searcher::Node> result;
				cout << "key : " << value << endl;	
			
				//spawns a searcher thread and waits for it to finist

				{ //COBEGIN
				Searcher::Searcher s(multiset, value, result,
														 0, multiset.size(), 	multisetIter);
				} //COEND


				//prints and formats the results
				if (result.size() == 1){
					cout << "Found " << result.size() << " match for key " << value << endl;
				}

				else {
					cout << "Found " << result.size() << " matches for key " << value << endl;
				}
		
				outputResult(result);
				result.clear();	
				cout << endl;



}

/* A helper function reads the keys from standard input
*	INPUTS
* 		list<Searcher::Node> &multiset - the list which the search is performed on
*	OUTPUT
*			void
*/
void readstd(list<Searcher::Node> &multiset){

	string inputLine;
		int value;
		//parses out the newlines
		while ( std::getline ( std::cin, inputLine )) {
			stringstream iss(inputLine);
			//parses out the whitespace
			while (iss >> value){
				
				//perform search on the key
				search(multiset, value);

			}
		}
}


void uMain::main() {

	list<Searcher::Node> multiset;	
	list<int> keys;

	//if there is one argument
	if (argc == 2){
		//read the data file
		readMultiset(multiset, argv[1]);
		//read keys from stdin
		readstd(multiset);
		
	}

	//if there are two arguments
	else if (argc == 3){
		//read the data file
		readMultiset(multiset, argv[1]);
		//read keys file
		readKeys(keys, argv[2]);


		list<Searcher::Node>::iterator multisetIter = multiset.begin();
		
		//iterate over the keys and run a search on each key
		list<int>::iterator keyIter;
		for(keyIter = keys.begin(); keyIter != keys.end(); keyIter++){
			search(multiset, *keyIter);
		}

	}

	//else incorrect number of arguments
	else {
		cerr << "Usage: ./searcher multiset-file [ searchkeys-file ]" << endl;
	}

	


}
