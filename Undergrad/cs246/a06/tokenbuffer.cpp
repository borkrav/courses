#include "tokenbuffer.h"


void TokenBuffer::inputCookedTokensIntoBuffer(){
		
	Token temp;
	temp.inputCookedToken();
	
	while (temp.getHead() != 'E'){
		buffer.push_back(temp);
		temp.inputCookedToken();
	} 
	
	buffer.push_back(temp);
	
	
}


void TokenBuffer::outputCookedTokensFromBuffer(){
	rewind();
	
	for (int i = 0; i < buffer.size(); i++) {
		Token next = getToken();
		next.outputCookedToken();
		
	}
	
		
}





void TokenBuffer::outputRawTokensFromBuffer(){
	
	rewind();
	
	for (int i = 0; i < buffer.size(); i++) {
		Token next = getToken();
		
		if (next.getHead() == ';') {
			std::cout << next << std::endl;
		}
		
		else {
			std::cout << next;
		}
	}
}




void TokenBuffer::rewind ( ){
	it = buffer.begin();
}




	
Token TokenBuffer::getToken(){
	
	Token next = *it;
	it++;
	
	return next;
}
	
	










