#include "pizzaobject.h"
#include "pizzadata.h"
#include <iostream>
using namespace std;

pizzaobject::pizzaobject(){
	total = 0;
	numberOfToppings = 0;
	orderToppings.resize(100);
	
}


void pizzaobject::recordSize(int index){
	cout << sizeName[index] << endl;
	orderSize = (char *)sizeName[index];
	calculateOrder(pizzaPrice[index]);
}

void pizzaobject::recordTopping(int index){
	cout << toppingName[index] << endl;
	orderToppings[numberOfToppings] = (char *)toppingName[index];
	numberOfToppings += 1;
	calculateOrder(toppingPrice[index]);
}

double pizzaobject::printOrder(){
	
	return total;	
}

void pizzaobject::calculateOrder(double price){
	total += price;
}

int pizzaobject::countToppings(int index){
	
	int counter = 0;
	
	for (int k = 0; k < numberOfToppings; k++) {
		if (orderToppings[k] == toppingName[index]) {
			counter += 1;
			
		}
	}
	
		return counter;
}

char* pizzaobject::printSize(){
	return orderSize;
}

	
