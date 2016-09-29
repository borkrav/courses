#include "pizzadata.h"
#include <iostream>

using namespace std;

void printMenu(){
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision (2);

	
	int sizes = (sizeof(sizeName))/8;
	int toppings = (sizeof(toppingName))/8 - 1;
	
	
	cout << "MENU FOR TONY'S PIZZA PLACE" << endl;
	cout << "There are " << sizes << " sizes of pizza:" << endl;

	cout << "  ";
	for (int i = 0; i < sizes; i++) {
		cout << sizeName[i] << " ($" << pizzaPrice[i] << ") ";
	}
	cout << endl;
	
	cout << "There is a choice of " << toppings << " toppings:" <<endl;
	
	cout << "  ";
	for (int i = 0; i < toppings; i++) {
		cout << toppingName[i] << " ($" << toppingPrice[i] << ") ";
	}	
	cout << endl;
}
	
	


//int main(){

//	printMenu();
	
//}