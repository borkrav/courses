#include "pizzadata.h"
#include "pizzaobject.h"
#include "pizzaok.h"
#include <iostream>
#include <stdlib.h>

using namespace std;


void indent(){
	cout << "    ";
}

bool verifySize (char input){
	return pizzaok(&input, SIZE_RANGE, BASIC_SIZE);
}

bool verifySize (int input){
	return pizzaok(&input, SIZE_RANGE, BASIC_SIZE);
}

bool verifyTopping (char input){
	return pizzaok(&input, TOPPING_RANGE, FIRST_TOPPING);
}
	
bool verifyTopping (int input){
	return pizzaok(&input, TOPPING_RANGE, FIRST_TOPPING);
}
	
int main(){
	
	pizzaobject order;
	
	char input = 0;
	int input1 = 0;
	int index = 0;

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision (2);

	cout << helloPhrase;
	cout << sizePrompt;
	
	indent();
	
	
	for (int i = 0; i< SIZE_RANGE; i++){
		
		cout << (char) (BASIC_SIZE+i) << "=" << sizeName[i] << " ";
	}
	
	cin >> input;
	
	
	if (verifySize(input) == 1){
		//pass in item and price to object
		indent();
		index = -(BASIC_SIZE - input);
		order.recordSize(index);
	}
	
	else {
		cout << abortPhrase << " '" << input << "'"<< endl;	
		exit(0);
	}
		
	
	while (input1 != TOPPING_RANGE) {
		
		cout << toppingPrompt;
		indent();
		for (int i = 0; i< TOPPING_RANGE; i++){
			
			cout << (char) (FIRST_TOPPING+i) << "=" << toppingName[i] << " ";
		}
		
		cin >> input1;
			
		if (verifyTopping(input1)) {
			indent();
			index = input1-1;
			order.recordTopping(index);
		}
		
		else {
			cout << abortPhrase << " '" << input1 << "'"<< endl;	
			exit(0);
		}
		
		
		

	}
	
	cout << "You have ordered pizza of size " << order.printSize() << endl;
	cout << "Your toppings are " << endl;
	
	cout << " ";
	indent();
	for (int i = 0; i < TOPPING_RANGE-2; i++) {		
		
		cout << order.countToppings(i) << " " << toppingName[i] << " ";
	}
	
	cout << order.countToppings(TOPPING_RANGE-2) << " " << toppingName[TOPPING_RANGE-2];

	
	cout << endl;
	
	cout << "Please pay $" << order.printOrder() << endl;
	cout << goodbyePhrase;

}
