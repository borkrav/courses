#include "q3grammar.h"

/* this looks at the current ch value, and returns one of the statuses 
depending on the current state of the coroutine */

void Grammar::main(){
	yzCounter = 0;
	try {

		/* these statements iterate through the incoming charecters
		if there is a charecter mismatch, -1 is thrown, and the catch statement 
		sets the status to ERROR */

		if ( ch == 'x' ){
			status = CONT;
			suspend();
		}
		else throw -1;
	
		while ( ch == 'y' ){
			status = CONT;
			yzCounter+=1;
			suspend();
		}
	
		while ( ch == 'z' ){
			status = CONT;
			yzCounter+=1;
			suspend();
		}
	
		while ( ch == 'u' ){
			if ( yzCounter == 0 ){
				throw -1;
			}
			status = CONT;
			yzCounter--;
			suspend();
		}

		if ( yzCounter != 0 ){
			throw -1;
		}
	
		if ( ch == 'v' ){
			status = MATCH;
		}
		else throw -1;

	} catch ( int e ) {
		status = ERROR;
	}

}
