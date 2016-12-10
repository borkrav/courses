// Problem1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


typedef struct element {

	element* next;
	int data;

};


//Create stack data structure using linked lists

// Pop function
// Remove the first item of the stack (Head)

// input: **stack, *data
// output: true or false (error checking)

bool pop(element **elem, int *data) {

	if (*elem == NULL) {
		return false;
	}

	else {
		*data = (*elem)->data;
		element* head = (*elem)->next;
		delete *elem;
		*elem = head;
		return true;
	}

}


// Push function 
// Add a new head item to the stack

// input: **stack, *data
// output: true or false (error checking)

//elem may be a null stack, elem should be initialized to null

bool push(element** elem, int data) {

	try {
		element* newElem = new element;
		newElem->data = data;
		newElem->next = *elem;
		*elem = newElem;
		return true;
	}

	catch (std::bad_alloc& exc) {
		return false;
	}
}



// Create function
// Create a new stack - for a linked list, this doesn't have to do anything
// input: **stack

bool createStack (element** elem){
	*elem = NULL;
	return true;
}

// Delete stack
// Input: **stack

bool deleteStack(element **elem) {

	//keep calling pop on the stack until we reach the last element

	int data = 0;

	while (pop(elem, &data));

	return true;


}




int main()
{

	element* stack = NULL;

	int data = 0;


	//initialize stack
	createStack(&stack);

	//push on some values

	cout << push(&stack, 1) << endl;
	cout << push(&stack, 2) << endl;
	cout << push(&stack, 3) << endl;
	cout << push(&stack, 4) << endl;

	//pop some values

	cout << pop(&stack, &data) << endl;
	cout << data << endl;
	cout << pop(&stack, &data) << endl;
	cout << data << endl;
	cout << pop(&stack, &data) << endl;
	cout << data << endl;
	cout << pop(&stack, &data) << endl;
	cout << data << endl;

	//another pop on an empty stack
	cout << pop(&stack, &data) << endl;

	//tear down stack

	deleteStack(&stack);


	//keep window open
	int a;
	cin >> a;
    return 0;

}

