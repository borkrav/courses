#include "token.h"

Token::Token(char hd, std::string tl){
	head = hd;
	tail = tl;
}

Token::Token(char hd){
	head = hd;
	tail = "";
}

Token::Token(){
	head = ' ';
	tail = "";
}


bool Token::isSkinny(){
	
	if (head == 'x'|| head == '"') {
		return 0;
	}
	
	return 1;
}

char Token::getHead(){
	return head;
}

std::string Token::getTail(){
	return tail;
}

void Token::inputCookedToken(){
	
	char hd;
	std::string tl;

	std::cin >> hd;
	
	if (hd == 'x' || hd == '"') {
		head = hd;
		std::cin >> hd;
		std::cin >> tl;
		tail = tl;
	}
	
	else {
		head = hd;
		tail = "";
	}

}

void Token::outputCookedToken(){
	
	if (isSkinny()) {
		std::cout << head << std::endl;
	}
	
	else {
		std::cout << head << ":" << tail << std::endl;
	}

}

std::ostream& operator << (std::ostream & os, const Token & tok){
	
	Token t = tok;
	
	
	if (t.head == 'E'){
		return os;
	}
	
	else if	(t.head =='e'){
		os << "==" << " ";
	}
	
	else if (t.isSkinny()) {
		os << t.head << " ";
	}
	
	else if (t.head == '"') {
		os << '"' << t.tail << '"' << " ";
	}

	else {
		os << t.tail << " ";
	}
	return os;
}
		
		


