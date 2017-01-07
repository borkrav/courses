// Problem3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;



typedef struct element {
	int data;
	element* next;
};

//add an element to the list
//no edge cases here, pretty straight forward, only if alloc fails

bool addData(element **head, int data) {

	try {

		element* elem = new element;
		elem->data = data;
		elem->next = *head;
		*head = elem;
		return true;
	}

	catch (std::bad_alloc exc) {
		return false;
	}
}



//destroy the list
//no edge cases here either
void destroyList(element ** head) {

	while (*head != NULL) {
		element *newHead = (*head)->next;
		delete *head;
		*head = newHead;
	}
}

void printList(element ** head) {

	element *current = *head;

	while (current != NULL) {
		cout << current->data << " ";
		current = current->next;
	}

	cout << endl;

}


//time and space efficient algorithm to find the mth to last element of the list
//when m=0, return last element

//approach - go through linked list to determine the length as first pass, return element as second pass
// - O(1) space, O(n) time

//could also just copy over all elements to an array, saving on the second pass
// - O(n) space, O(n) time

//best solution - keep the element that is m spots behind you in memory

//edge cases
//m < 0, m > length, list is null

bool mthToLast(element **head, int m, int *result) {

	if (*head == NULL || m < 0) {
		return 0;
	}

	//first pass - determine how long the list is

	element* current = *head;

	element* temp = NULL;

	int length = 0;

	while (current != NULL) {
		
		if (length == m) {
			temp = *head;
		}

		if (length > m) {
			temp = temp->next;
		}

		length+=1;
		current = current->next;
	}

	if (temp == NULL) {
		return 0;
	}

	*result = temp->data;
	return 1;


}







int main()
{

	element *linkedList = NULL;

	printList(&linkedList);

	addData(&linkedList, 0);
	addData(&linkedList, 1);
	addData(&linkedList, 2);
	addData(&linkedList, 3);
	addData(&linkedList, 4);
	addData(&linkedList, 5);
	addData(&linkedList, 6);
	addData(&linkedList, 7);
	addData(&linkedList, 8);
	addData(&linkedList, 9);
	printList(&linkedList);

	int result = -9;

	mthToLast(&linkedList, 10, &result);
	cout << result << endl;


	destroyList(&linkedList);


	int a = 0;
	cin >> a;

    return 0;
}

