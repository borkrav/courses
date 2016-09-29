#include "q3searcher.h"


//the task main
void Searcher::main(){

	//base case - if the partition size is smaller than 10, do a linear search
	if (_high-_low <=10){
		for (int i = 0; i<_high-_low; i++){
			
			//if there's a match, push back node onto the result
			if (_start->key == _key){
				_locns->push_back(Node(_low+i, _start->value));
			}
			_start++;
		}
	}
	
	else {

		//calculate the partition split
		//child thread gets front half
		//parent thread gets back half
		int myLow = (_high+_low)/2+1;
		int myHigh = _high;
		int childLow = _low;
		int childHigh = (_high+_low)/2;
		list<Node>::iterator childStart =_start;
		advance(_start, (_high+_low)/2);

		//spawn a child thread to search the front half of the list
		Searcher(*_multiset, _key, *_locns, childLow, childHigh, childStart);

		//search the back half of the list
		for (int i = 0; i<=myHigh-myLow; i++){
			
			//if there's a match, push back node onto the result
			if (_start->key == _key){
				_locns->push_back(Node(myLow+i-1, _start->value));
			}
			_start++;
		}

	}

}


/* The searcher constructor
*	INPUTS
* 		list<Node> &multiset - the reference to the multiset list
*			int key - the key we're searching for
*			list<Node> &locns - the reference to the result list
*			unsigned int low - starting index
*			unsigned int high - the ending index
*			list<Node>::iterator &start - the reference to iterator that points to the starting index
*/
Searcher::Searcher( list<Node> &multiset, int key, list<Node> &locns,
              unsigned int low, unsigned int high, list<Node>::iterator &start ){

	_multiset = &multiset;
	_key = key;
	_locns = &locns;
	_low = low;
	_high = high;
	_start = start;

}

