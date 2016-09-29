#include "q1kvqueue.h"
#include <iostream>

using namespace std;


KVQueue::KVQueue(int size){

	queue = deque<Mapper::KeyValue>();

	//the required synch primitives
	empty = new uSemaphore(size);
	full = new uSemaphore(0);
	lock = new uSemaphore(1);
	
}

KVQueue::~KVQueue(){

	delete empty;
	delete full;
	delete lock;


}

void KVQueue::pushBack(const Mapper::KeyValue& item){

	empty->P();
	lock->P();

	queue.push_back(item);

	lock->V();
	full->V();

}

Mapper::KeyValue KVQueue::popFront(){

	lock->P();
	full->P();

	Mapper::KeyValue value = queue.front();
	queue.pop_front();

	empty->V();
	lock->V();
	return value;
	
}

int KVQueue::peekFront(Mapper::KeyValue* val){

	lock->P();

	int retval;

	if (!queue.empty()){
		val->key = queue.front().key;
		val->value = queue.front().value;
		retval = 0;
	}
	
	else retval = -1;
	
	lock->V();
	return retval;

}
