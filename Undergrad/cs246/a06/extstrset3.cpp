#include "extstrset3.h"
#include <iostream>

extStrSet::extStrSet(){

	strSet a;
	*this = ss2extss(a);
	
	
}


extStrSet::extStrSet(std::string s){

	strSet a(s);
	*this  = ss2extss(a);
}


extStrSet extStrSet::operator == (const extStrSet& rtSide){
	
	extStrSet yes("true");
	extStrSet no("false");

	if (this == &rtSide) {
		return yes;
	}
	
	if (isNull() || rtSide.isNull()) {
		return no;
	}

	strSet test;
	test = *this - rtSide;
	test = ss2extss(test);
	
	if (test.isNull() && SIZE() == rtSide.SIZE()) {
		return yes;

	}
	
	else {
		return no;

	}
}
	

extStrSet extStrSet::operator <  (const extStrSet& rtSide){
	
	extStrSet yes("true");
	extStrSet no("false");
	
	if (this == &rtSide) {
		return no;
	}
	
	if (isNull() || rtSide.isNull()) {
		return no;
	}
	
	strSet test;
	test = *this - rtSide;
	test = ss2extss(test);
	
	if (test.isNull() && rtSide.SIZE()>SIZE()) {
		return yes;
		
	}
	
	else {
		return no;
		
	}
	
	
}


extStrSet extStrSet::operator >  (const extStrSet& rtSide){
	
	extStrSet yes("true");
	extStrSet no("false");
	
	if (this == &rtSide) {
		return no;
	}
	
	if (isNull() || rtSide.isNull()) {
		return no;
	}
	
	strSet test;
	test = *this - rtSide;
	test = ss2extss(test);
	
	if (!test.isNull()) {
		return yes;
		
	}
	
	else {
		return no;
		
	}
}
	
	
	
std::ostream& operator <<(std::ostream & os, const extStrSet & ess){

	
	//os << (strSet)(ess).output();
	
	
	
       	extStrSet::myNode * next = ess.first;
	
	if (next == NULL || next->str == "NULL") {
		os << "Empty set" << std::endl;
	}
	
	else {
		while (next != NULL) {
			os << next->str << std::endl;
			next = next->next;
		}
		
	}
	
	
	/*
	for (int i = 0; i< ess.SIZE(); i++) {
		os << ess.strVector[i] << std::endl;
	}

	return os;
	*/
}
