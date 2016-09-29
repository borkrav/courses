#include "strset.h"
#include <iostream>
using namespace std;

strSet::strSet(){
	strVector.resize(0);
}


strSet::strSet(string s){
	strVector.resize(1);
	strVector[0] = s;
}

void strSet::nullify(){
	strVector.resize(0);
}


bool strSet::isNull() const{
	if (strVector.size() == 0){
		return 1;
	}
	
	else return 0;
}


int strSet::SIZE() const{
	return strVector.size();
}

void strSet::output() const{
	for (int i = 0; i<SIZE(); i++) {
		cout << strVector[i] << endl;
	}
}

bool strSet::isMember (string s) const{
	for (int i = 0; i<SIZE(); i++){
		if (strVector[i] == s){
			return 1;
		}
	}
	return 0;
}

strSet strSet::operator +  (const strSet& rtSide){

	if (strVector.size() == 0){
		return rtSide;
	}
	
	
	strSet result;
	result.strVector = strVector;

	for (int i = 0; i < rtSide.SIZE(); i++) {
		
		if (!isMember(rtSide.strVector[i])) {
			
			string item = rtSide.strVector[i];
						
			int size = result.SIZE();
						
			int j = 0;
			
			while (j < size){
				
				if(size == 1 && item > result.strVector[j]){
					result.strVector.push_back(item);
					j = size;
				}
				
				if(size == 1 && item < result.strVector[j]){
					result.strVector.insert(result.strVector.begin(), item);
					j = size;
				}
				
				if (item > result.strVector[j] && item < result.strVector[j+1]) {
					result.strVector.insert(result.strVector.begin()+j+1, item);
					j = size;
				}
				
				if (item < result.strVector[1]) {
					result.strVector.insert(result.strVector.begin(), item);
					j = size;
				}
				
				if(j+2 == size){
					result.strVector.push_back(item);
					j = size;
				}
				
				else {
					j++;
				}
				
			}

		}		
	}
	return result;
}
	

strSet  strSet::operator - (const strSet& rtSide){
	
	strSet result;
	result.strVector = strVector;
	
	for (int i = 0; i < rtSide.SIZE(); i++) {
		
		for (int j = 0; j<result.SIZE(); j++) {
			
			if (result.strVector[j] == rtSide.strVector[i]) {
				result.strVector.erase(result.strVector.begin()+j);
			} 
			
		}
	
	}
	
	return result;
	
	
}


strSet  strSet::operator *  (const strSet& rtSide){
	
	strSet result;
	
	for (int i = 0; i < rtSide.SIZE(); i++) {
		
		for (int j = 0; j < SIZE(); j++) {
			
			if (strVector[j] == rtSide.strVector[i]) {
		
				result.strVector.push_back(strVector[j]);
				
			} 
			
		}
		
	}
	
	return result;
}


strSet & strSet::operator = (const strSet& rtSide){
	
	if (this == &rtSide){
		return *this;
	}
	
	else{
		nullify();
		strVector = rtSide.strVector;
		return *this;
	}
	
	
}
	
	
