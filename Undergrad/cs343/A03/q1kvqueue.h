#ifndef _Q1KVQUEUE_H
#define _Q1KVQUEUE_H

#include <uC++.h>
#include "q1mapper.h"
#include <deque>

class KVQueue {

	private:
		deque<Mapper::KeyValue> queue;
		uSemaphore *empty, *full, *lock;


  public:
    KVQueue(int size);
		~KVQueue();
    void pushBack(const Mapper::KeyValue& item);
    Mapper::KeyValue popFront();
    // Copy the front value to "val" without removing it from the queue.
    // Return 0 on success and -1 if the queue is empty.
    int peekFront(Mapper::KeyValue* val);
};

#endif
