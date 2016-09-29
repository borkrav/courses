#include "strset2.h"
#include <iostream>
using namespace std;

strSet::strSet(){
	first = NULL;
}


strSet::strSet(string s){
	node *temp = new node;
	temp->data = s;
	temp->next = NULL;	

	first = temp;
}


void strSet::copyList(const strSet &cp){

	node * copy = cp.first;
	
	node * temp = new node;
	temp->data = copy->data;
	temp->next = NULL;
	node * last = temp;
	first = temp;
	
	copy = copy->next;
    
	if (cp.SIZE() > 1) {
		while (copy != NULL) {
			node * temp = new node;
			last->next = temp;
			
			temp->data = copy->data;
			temp->next = NULL;
			last = temp;
			copy = copy->next;
			
		}
		
	}
	
}


strSet::strSet(const strSet &cp){
	
	copyList(cp);
	
}

void strSet::nullify(){
	
	if (first == NULL) {
		//do nothing
	}
	
	else if (first->next != NULL) {
	
		while (first->next != NULL) {
			node * next = first->next;
			delete first;
			first = next;
		}
		delete first;
		first = NULL;
	}
	
	else {
		delete first;
		first = NULL;
	}

		
}


bool strSet::isNull() const{
	if (first == NULL){
		return 1;
	}
	
	else return 0;
}


int strSet::SIZE() const{
	int counter = 0;
	node * next;
	
	if (first == NULL) {
		return 0;
	}
	
	else {
		next = first;
		
		while (next != NULL) {
			next = next->next;
			counter+=1;
		}
		return counter;
	}


	
}

void strSet::output() const{

	node * next = first;
	
	if (next == NULL || next->data == "NULL") {
		cout << "Empty set" << endl;
	}

	else {
		while (next != NULL) {
			cout << next->data << endl;
			next = next->next;
		}
		
	}

}

bool strSet::isMember (string s) const{
	
	node * next = first;
	
	while (next != NULL) {
		if (next->data == s) {
			return 1;
		}
		next = next->next;
	}
	
	return 0;
	
}

strSet strSet::operator +  (const strSet& rtSide){
	
	if (&rtSide == this) {
		strSet result(rtSide);
		return result;
	}
	
	else if (isNull()) {
		strSet result(rtSide);
		return result;
	}
	
	else if (rtSide.isNull()) {
		strSet result(*this);
		return result;
	}
	
	
	else {
		node * left = first;
		node * right = rtSide.first;
		
		strSet result;
		
		node * empty = new node;
		
		node * last = empty;
		result.first = last;
				
		while (!(left == NULL && right == NULL)) {
			
			node * temp = new node;
			last->next = temp;
			last = temp;
			
			if (left == NULL) {
				temp->data = right->data;
				right = right -> next;
			}
			
			else if (right == NULL) {
				temp->data = left->data;
				left = left -> next;
			}
			
			
			else if (left->data < right->data) {
				temp->data = left->data;
				left = left->next;
			}
			
			else if (right->data < left->data) {
				temp->data = right->data;
				right = right->next;
			}
			
			
			else if (right->data == left->data) {
				temp->data = left->data;
				left = left->next;
				right = right->next;
			}			
			
		}
		
		last->next = NULL;
		
		result.first = result.first->next;
		delete empty;
		
		return result;
	}
	
}


strSet  strSet::operator - (const strSet& rtSide){
	
	if (&rtSide == this) {
		strSet result("NULL");
		return result;
	}
	
	else if (isNull()) {
		strSet result("NULL");

		return result;
	}
	
	else if (rtSide.isNull()) {
		strSet result(*this);
		return result;
	}
	
	
	else {
		node * left = first;
		node * right = rtSide.first;
		
		strSet result;
		
		node * empty = new node;
		bool run = true;
		
		node * last = empty;
		result.first = last;
		
		while (!(left == NULL && right == NULL) && run) {
			
			
			
			if (left == NULL) {
				run = false;
			}
			
			else if (right == NULL) {
				node * temp = new node;
				last->next = temp;
				last = temp;
				
				temp->data = left->data;
				left = left -> next;
			}
			
			
			else if (left->data > right->data) {
				right = right->next;
			}
			
			
			else if (left->data != right->data) {
				node * temp = new node;
				last->next = temp;
				last = temp;
				
				temp->data = left->data;
				left = left->next;
			}
			
			else if (left->data == right->data) {
				left = left->next;
				right = right->next;
			}
			

			
		}
		

		
		last->next = NULL;
		
		result.first = result.first->next;
		delete empty;
		
		if (result.SIZE() == 0) {
			node * temp = new node;
			temp->data = "NULL";
			temp->next = NULL;
			result.first = temp;
		}
	
		return result;
	}
	
	
}


strSet  strSet::operator *  (const strSet& rtSide){
	
	if (&rtSide == this) {
		strSet result(*this);
		return result;
	}
	
	else if (isNull()) {
		strSet result("NULL");
		return result;
	}
	
	else if (rtSide.isNull()) {
		strSet result("NULL");
		return result;
	}
	
	
	else {
		node * left = first;
		node * right = rtSide.first;
		
		strSet result;
		
		node * empty = new node;
		
		node * last = empty;
		result.first = last;
		
		while (!(left == NULL && right == NULL)) {
			

			if (left == NULL) {
				break;
			}
			
			else if (right == NULL) {
				break;
			}
			
			
			else if (right->data == left->data) {
				node * temp = new node;
				last->next = temp;
				last = temp;
				
				temp->data = left->data;
				left = left->next;
				right = right->next;
			}
			
			
			else if (left->data < right->data) {
				left = left->next;
			}
			
			else if (left->data > right->data) {
				right = right->next;
			}
		
		}
		
		
		
		last->next = NULL;
		
		result.first = result.first->next;
		delete empty;
		
		
		if (result.SIZE() == 0) {
			node * temp = new node;
			temp->data = "NULL";
			temp->next = NULL;
			result.first = temp;
		}
		
		
		
		
		return result;
	}
	
	
	
	
}


strSet & strSet::operator = (const strSet& rtSide){
	
	if (this == &rtSide){
		return *this;
	}
	
	else{
		nullify();
		copyList(rtSide);
		return *this;
		
	}
	
	
}

