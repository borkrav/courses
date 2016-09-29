#include "stdlib.h"
#include "token.h"
#include "tokenbuffer.h"
#include "tokennames.h"
#include "strset3.h"
#include "extstrset3.h"
#include "string.h"
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

TokenBuffer source;
vector<Token> line;
map<string,strSet> symbolTable;
vector<string> variables;

void program();
void statements(vector<Token> line);
void declaration(vector<Token> line);
void assignment(vector<Token> line);
void output(vector<Token> line);
void read(vector<Token> line);
void write(vector<Token> line);
strSet expression(vector<Token> line);
void print(vector<Token> line);
strSet comparison(vector<Token> line);
strSet term(vector<Token> line);
strSet factor(vector<Token> line);
vector<Token> getLine();
void printLine(vector<Token> a);
bool checkVariable(string s);
void enter();

	

int main(){

	source.inputCookedTokensIntoBuffer();
	
	source.rewind();

	program();

}


void program(){
	
	line.resize(100);

	line = getLine();

	
	while (line.size() != 0) {
		
	statements(line);
	
	line = getLine();
		
	}
	
	
	

	
}

void statements(vector<Token> line){

	
	if (line.size() == 2 &&
		line[0].getHead() == identifierToken && line[0].getTail() == "print" && 
		line[1].getHead() == stringToken){
		
		print(line);
	}
	
	else if	(line.size() == 2 &&
			 line[0].getHead() == identifierToken && line[0].getTail() == "output" && line[1].getHead() == identifierToken){
		output(line);
	}
	
	
	else if (line[0].getHead() == identifierToken && line[0].getTail() == "set" &&
			 line[1].getHead() == identifierToken &&
			 line[2].getHead() == assignToken) {
		declaration(line);
	}
	
	else if (line[0].getHead() == identifierToken && line[1].getHead() == assignToken) {
		assignment(line);
	}
	
	
		
	else if (line.size() == 4 &&
			 line[0].getHead() == identifierToken && line[0].getTail() == "read" &&
			 line[1].getHead() == identifierToken && 
			 line[2].getHead() == identifierToken && line[2].getTail() == "from" &&
			 line[3].getHead() == stringToken){
		
		read(line);
	}
	
	else if (line.size() == 4 &&
			 line[0].getHead() == identifierToken && line[0].getTail() == "write" &&
			 line[1].getHead() == identifierToken && 
			 line[2].getHead() == identifierToken && line[2].getTail() == "to" &&
			 line[3].getHead() == stringToken){
		
		write(line);
	}
	
	

		
	else {
		cerr << "BAD SYNTHAX" << endl;
		exit(0);
	}

}


void print (vector<Token> line){
	
	cout << line[1].getTail() << endl;
	
}

void declaration(vector<Token> line){
	strSet empty;
	string name = line[1].getTail();
		
	line.erase(line.begin());
	line.erase(line.begin());
	line.erase(line.begin());

	if (checkVariable(name) == 1) {
		cerr << "MULTIPLE DECLATARION" << endl;
		exit(0);
	}
	
	empty = expression(line);
	
	symbolTable[name] = empty;
	variables.push_back(name);
	
}


void assignment(vector<Token> line){
	
	string name = line[0].getTail();
	
	if (checkVariable(name) == 0) {
		cerr << "UNDECLARED SET" << endl;
		exit(0);
	}

	strSet assign;
	
	line.erase(line.begin());
	line.erase(line.begin());
	
	assign = expression(line);
	
	symbolTable[name] = assign;
	
	
	
}


strSet expression(vector<Token> line){
	

	bool less = false;
	bool greater = false;
	bool equals = false;
	
	
	for (int i = 0; i < line.size(); i++) {
		if (line[i].getHead() == gtrToken) {
			greater = true;
		}
		
		if (line[i].getHead() == lessToken) {
			less = true;
		}
		
		if (line[i].getHead() == equalToken) {
			equals = true;
		}
		
	}
	
	
	if ((line.size() > 1 && less) || (line.size() > 1 && greater) || (line.size() > 1 && equals)) {
		
		vector<Token> right;
		vector<Token> left;
		int i = 0;
		
		for (i; line[i].getHead() != lessToken && line[i].getHead() != gtrToken && line[i].getHead() != equalToken; i++) {
			left.push_back(line[i]);
		}
		
		
		for (i+=1 ; i < line.size(); i++) {
			right.push_back(line[i]);
		}
		
		if (less) {
			
			strSet lresult = comparison(left);
			strSet rresult = expression(right);
			strSet result;
			
			ss2extss(result) = ss2extss(lresult) < ss2extss(rresult);
			
			
			return result;
			
			
		}
		
		if (greater) {
			
			strSet lresult = comparison(left);
			strSet rresult = expression(right);
			strSet result;
			
			ss2extss(result) = ss2extss(lresult) > ss2extss(rresult);
			
			
			return result;
			
			
		}
		
		if (equals) {
			
			strSet lresult = comparison(left);
			strSet rresult = expression(right);
			strSet result;
			
			ss2extss(result) = ss2extss(lresult) == ss2extss(rresult);
			
			
			return result;
			
			
		}
		
		
	}
	
	else {
		return comparison(line);
	}


	
}

strSet comparison(vector<Token> line){
	
	bool plus = false;
	bool minus = false;
	string operation = "null";
	int number = 0;
	
	
	
	for (int i = 0; i < line.size(); i++) {
		if (line[i].getHead() == plusToken) {
			plus = true;
			operation = "plus";
			number ++;
		}
		if (line[i].getHead() == minusToken) {
			minus = true;
			operation = "minus";
			number ++;
		}
	}
	
	
	if ((line.size() > 2 && plus) || (line.size() > 2 && minus)) {
		
		vector<Token> right;
		vector<Token> left;
		
		int i = 0;
		int j = number;
		bool bracket = false;
		
		if (line[0].getHead() == leftParenToken) {
			i = 1;
		}
		
		
		for (i;  j > 0; i++) {
			
			if (line[i].getHead() == rightParenToken) {
				bracket = true;
				j = 0;
			}
			
			if (line[i].getHead() == plusToken || line[i].getHead() == minusToken){
				j--;
			}
			
			left.push_back(line[i]);
		}
		
		left.erase(left.end());
		
		if (bracket) {
			i++;
		}
		
		for (i ; i < line.size(); i++) {
			right.push_back(line[i]);
		}
		
	
		
		strSet result = comparison(left);
		
		if (operation == "plus") {
			result = result + term(right);
		}
		
		if (operation == "minus") {
			result = result - term(right);
		}
		
		return result;
		
	}
	
	else {
		return term(line);
	}
	

	
}



strSet term(vector<Token> line){
	
	
	bool mult = false;
	
	
	
	for (int i = 0; i < line.size(); i++) {
		if (line[i].getHead() == multiplyToken) {
			mult = true;
		}
	}
	
	if (line.size() > 2 && mult) {
		
		
		vector<Token> right;
		vector<Token> left;
		int i = 0;
		
		for (i; line[i].getHead() != multiplyToken; i++) {
			left.push_back(line[i]);
		}
		
		
		for (i+=1 ; i < line.size(); i++) {
			right.push_back(line[i]);
		}
		
		
		strSet result = factor(left);

		result = result * term(right);
		
		return result;
		
			
		
		
	}

		
	else {
		return factor (line);
	}
	
}

strSet factor(vector<Token> line){
	

	if (line.size() == 1 && !line[0].isSkinny()) {
		
		string name = line[0].getTail();
		
		if (checkVariable(name) == 0) {
			cerr << "UNDECLARED SET" << endl;
			exit(0);
		}
		
		strSet result = symbolTable[name];
		return result;
	}
	
	else if (line[0].getHead() == leftBraceToken){
		
		strSet result;
		
		for (int i = 1; line[i].getHead() != rightBraceToken ; i++) {
			
			
			
			if (line[i].getHead() != stringToken) {
				cerr << "SYNTHAX ERROR 1";
				exit(0);
			}
			
			else {
				strSet single(line[i].getTail());
				result = result + single;
			}
			
		}
		
		
		for (int i = 0; line[i].getHead() != rightBraceToken;) {
			line.erase(line.begin());
		}
		
		line.erase(line.begin());
				
				
		if (line.size() > 1) {
			cerr << "SYNTHAX ERROR 2";
			exit(0);
		}
		
				
		return result;
		
		
		
	}
	
	else if (line[0].getHead() == leftParenToken){
		
		vector<Token> noBrace;
		
		for (int i = 1; line[i].getHead() != rightParenToken ; i++) {
			
			noBrace.push_back(line[i]);
		}
		
		line = noBrace;
						
		return expression(line);
		
	}
	
	else {
		cerr << "SYNTHAX ERROR 3" << endl;
		exit(0);
	}

		
		
		
		
		
	
	
}




void output(vector<Token> line){
	
	if (line.size() > 2) {
		cerr << "SYNTHAX ERROR 4" << endl;
	}
	
	else {
		
		string variable = line[1].getTail();
		
		
		if (checkVariable(variable) == 0) {
			cerr << "UNDECLARED SET";
			exit(0);
		}
		
		else {
			strSet out = symbolTable[variable];
			
			if (out.isNull() == 1) {
				cout << "Empty Set" << endl;
			}
			
			else {
				out.output();
			}
		}
		
	}
	
}



void write(vector<Token> line){
	
	string variable = line[1].getTail();
	
	if (checkVariable(variable) == 0) {
		cerr << "UNDECLARED SET";
		exit(0);
	}
	
	strSet set = symbolTable[variable];
	string file = line[3].getTail();
	
	
	const char* cs (file.c_str());
	
	
	ofstream output;
	output.open(cs);
	output << ss2extss(set);
	output.close();
	
	
}

void read(vector<Token> line){
	
	string variable = line[1].getTail();
	
	if (checkVariable(variable) == 0) {
		cerr << "UNDECLARED SET";
		exit(0);
	}
	
	strSet set;
	symbolTable[variable].nullify();
	
	
	string file = line[3].getTail();
	
	
	const char* cs (file.c_str());
	
	
	fstream input;
	input.open(cs);
	
	string str;
	
	
	while (!input.eof()) {
		
		
		input >> str;
		strSet singleton(str);
		set = set + singleton;
		
	}
	
	input.close();
	
	symbolTable[variable] = set;
	
}


void enter(){
	cout << endl;
}


vector<Token> getLine(){
	
	vector<Token> line;
	
	Token read = source.getToken();
	
	while (read.getHead() != semicolonToken) {
		
		if (read.getHead() == EOFToken) {
			vector<Token> null;
			return null;
		}
		
		line.push_back(read);
		read = source.getToken();
	}
	
	return line;
}


void printLine(vector<Token> a){
	for (int i = 0; i<a.size(); i++) {
		a[i].outputCookedToken();
	}
}


bool checkVariable(string s){
	
	for (int i = 0; i<variables.size(); i++) {
		if (variables[i] == s) {
			return 1;
		}
	}
	
	return 0;
}
