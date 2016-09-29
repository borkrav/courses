#ifndef _Q1SORTMAPPER_H
#define _Q1SORTMAPPER_H

#include <uC++.h>
#include "q1mapper.h"
#include "q1kvqueue.h"
#include <map>
#include <set>

class KVQueue;

_Task SortMapper : public Mapper {
  private:
    void main();
		int _buffer_size;
		map<string,int> sortedBuffer;
		set<string> seenSoFar;
		
		

  public:
    // Writes items to the queue in sorted order.
    SortMapper(const string& filename, int queue_len, int buffer_size,
               uSemaphore* signal);
    virtual ~SortMapper();
};


#endif
