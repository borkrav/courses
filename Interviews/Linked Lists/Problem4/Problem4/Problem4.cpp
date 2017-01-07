// Problem4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



typedef struct Element {
	Element* next;
	int data;
};


//linked list cycle detection

//idea: check if the "next" pointer refers to any element I've already iterated over
//save all pointers I've already seen in a data structure, find out if element is in list

//O(1) lookup, O(1) insert, O(n) space, assuming a good hashing function is used

//edge cases - if passed in null list, return false

//O(n) runtime, since we're going to touch every element, O(n) space for the hashmap

//real solution - just use 2 pointers
//fast pointer, slow pointer



bool detectCycle(Element **head) {

	Element* slow = *head;
	Element* fast = *head;

	while (true) {
		if (fast == NULL || fast->next == NULL) {
			return false;
		}

		if (slow == fast || slow->next == fast) {
			return true;
		}

		slow = slow->next;
		fast = fast->next->next;

	}


}






int main()
{
    return 0;
}

