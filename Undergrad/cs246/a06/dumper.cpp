#include "token.h"
#include "tokenbuffer.h"
#include <iostream>
using namespace std;

int main(int argc,char *argv[]){
	
	
	
	TokenBuffer test;
	
	test.inputCookedTokensIntoBuffer();
	
	if (argc == 2) {
		test.outputCookedTokensFromBuffer();
	}
	
	else {
		test.outputRawTokensFromBuffer();

	}
	
	
	
	
}



