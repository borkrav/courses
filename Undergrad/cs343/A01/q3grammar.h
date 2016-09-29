#include <uC++.h>

_Coroutine Grammar {
public:
	enum Status { CONT, MATCH, ERROR }; // possible status
	
private:
	Status status; // current status of match
	char ch; // character passed by cocaller
	void main(); // coroutine main
	int yzCounter; // counter which keeps track of how many y's and z's have been seen so far
	
public:
	Status next( char c ) {
		ch = c; // communication in
		resume(); // activate
		return status; // communication out
	}
};
