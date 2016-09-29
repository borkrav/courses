#ifndef _Q1SORTREDUCER_H
#define _Q1SORTREDUCER_H

#include <uC++.h>
#include <uSemaphore.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "q1reducer.h"


_Task SortReducer : public Reducer {
  private:
    void main();
		map<string,int> _keys;
		map<string,int>::iterator _it;


  public:
    SortReducer(int id, int num_reducers, uSemaphore* signal,
                const vector<Mapper*>& mappers);
    virtual ~SortReducer();
};


#endif
