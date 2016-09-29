#include <uC++.h>
#include <iostream>
#include <fstream>
#include <string>

#include "q3grammar.h"

/* Checks whether the given input string is in the grammar or not
*	INPUTS
* 		string input -- the input string
* 	OUTPUTS
* 		void
*/
void checkString ( std::string input ){
	
	Grammar grammarInstance;
	int readSoFar = 0; //this keeps track of how many charecters have been read so far
	Grammar::Status finalStatus; //this is the final status returned by the coroutine


	//this iterates through the current input and feeds it charecter by charecter into the
	//grammar instance

	for ( int i = 0; i < input.length(); i+=1 ){
	
		Grammar::Status value = grammarInstance.next( input[i] );
		std::cout << input[i];
		readSoFar+=1;

		if ( value == Grammar::CONT ){
			finalStatus = Grammar::CONT;	
		}
		else if ( value == Grammar::MATCH ){
			finalStatus = Grammar::MATCH;			
			break;			
		}
		else if ( value == Grammar::ERROR ){
			finalStatus = Grammar::ERROR;
			break;			
		}
	}

	//the input matched and there are no extra charecters
	if ( readSoFar == input.length() && finalStatus == Grammar::MATCH ){
		std::cout << "\" yes" << std::endl;
	}

	//the input matched but there are extra charecters
	else if ( readSoFar != input.length() && finalStatus == Grammar::MATCH ){
		std::cout << "\" yes -- extraneous characters \"";
		for ( int i = readSoFar; i < input.length(); i+=1 ){
			std::cout << input[i];
		}
		std::cout << "\"" << std::endl;
	}
	
	//the input did not match and there are extra charecters
	else if ( readSoFar != input.length() ){
		std::cout << "\" no -- extraneous characters \"";
		for ( int i = readSoFar; i < input.length(); i+=1 ){
			std::cout << input[i];
		}
		std::cout << "\"" << std::endl;
	}

	//the input did not match or there wasn't enough input to get a match or error
	else if ( finalStatus == Grammar::ERROR || finalStatus == Grammar::CONT ){
		std::cout << "\" no" << std::endl;
	}


}

/* formats the output for a given inputLine string and checks if it is in the grammar
*	INPUTS
* 		string inputLine -- the input string
* 	OUTPUTS
* 		void
*/
void formatOutput( std::string inputLine ){

	//the input is a blank line
	if ( inputLine == "" ){
		std::cout << "\"" << inputLine
			 << "\" : Warning! Blank line." << std::endl;
	}
			
	//otherwise check if the line is in the grammar
	else {
		std::cout << "\"" << inputLine << "\" : \"";
		checkString( inputLine);
	}

}


void uMain::main() { // argc, argv class variables
	
	std::string inputLine;

	if ( argc == 2 ) { //there is an input file

		std::string fileName = argv[1];
		std::ifstream myfile;
		myfile.open( fileName.c_str() );

		//reads the file
		while ( getline(myfile, inputLine ) )
		{
			formatOutput( inputLine );
		}

		myfile.close();

	}

	else if ( argc == 1 ){ //there is no input file
		while ( std::getline ( std::cin, inputLine )) {
			formatOutput( inputLine );	
		}

	}
	
	else { //there are multiple input parameters
		std::cout << "Usage: ./grammar [infile-file]" << std::endl;
	}


}
