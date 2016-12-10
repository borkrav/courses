// Problem2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


using namespace std;


//defenition for the linked list
typedef struct Element {
	Element* next;
	int data;
};

Element *head;
Element *tail;

//Remove element

//input: Element* - element to be deleted
//output: true or false, depending on failed or not

//failure conditions - element not found in the list

//edge cases - tail == head == element, which will destroy the list

//

bool remove(Element *elem) {


	if (elem == NULL) {
		return false;
	}

	//is elem the head and tail?

	if (elem == head && elem == tail) {
		delete elem;
		head = NULL;
		tail = NULL;
		return true;
	}

	Element *current = head;
	Element *next = head->next;

	//is elem the head?

	if (elem == current) {
		delete elem;
		head = next;
	}

	//now traverse the list, until the tail

	while (elem != next) {
		current = next;
		next = current->next;

		//we've reached the tail, return false
		if (next == NULL) {
			return false;
		}
	}

	//elem == next

	Element *newNext = next->next;
	delete next;
	current->next = newNext;

	//check if we just deleted the tail
	if (newNext == NULL) {
		tail = current;
	}

	//done

	return true;


}

//insert element after given element

//input: Element* - element to insert after, int - interger data to insert
//output: boolean

//failure conditions
//none - we should always be able to insert

//edge cases
//empty list - we get a new head and tail
//insert at the beginning - we get a new head
//insert at the end - we get a new tail

bool insertAfter(Element *elem, int data) {

	//create the new element
	try {
		Element* newElem = new Element;
		newElem->data = data;
		newElem->next = NULL;

		//empty list?

		if (elem == NULL && tail == NULL) {
			head = newElem;
			tail = newElem;
			return true;
		}

		//inserting at the very beginning

		if (elem == NULL) {
			newElem->next = head;
			head = newElem;
			return true;
		}

		//now iterate through the list

		Element* current = NULL;
		Element* next = head;

		while (next != elem) {

			current = next;
			next = current->next;

			//we've reached the tail
			if (next == NULL) {
				return false;
			}

		}

		// next == elem

		current = next;
		next = current->next;
		current->next = newElem;
		newElem->next = next;

		//did we just insert a new tail?

		if (newElem->next == NULL) {
			tail = newElem;
		}

		return true;

	}

	catch (bad_alloc e) {
		return false;
	}

	

}


bool printList() {

	if (head == NULL) {
		cout << "empty list" << endl;
		return 0;
	}
	
	Element* current = head;

	cout << current->data << " ";

	while (current != tail) {
		current = current->next;
		cout << current->data << " ";
	}

	cout << endl;

	return 1;

}


int main()
{

	insertAfter(NULL, 5);
	insertAfter(NULL, 4);
	insertAfter(NULL, 3);
	insertAfter(NULL, 2);
	insertAfter(NULL, 1);

	printList();

	insertAfter(head->next, 0);
	printList();

	insertAfter(head, 7);
	printList();

	insertAfter(tail, 8);
	printList();

	remove(head->next);
	printList();

	remove(head);
	remove(tail);
	printList();

	remove(head);
	remove(head);
	remove(head);
	remove(head);
	remove(head);
	remove(head);
	printList();


	int a = 0;

	cin >> a;
	return 0;
}




//void removeHead(Node *head) {
//	delete head; /* Line 1 */
//	head = head->next; /* Line 2 */
//}


//void removeHead(Node **head) {
//  if (*head != null){
//  newHead = (*head)->next;
//  delete *head;
//  *head = newHead;
//  }
//}