#ifndef _Q1REDUCER_H
#define _Q1REDUCER_H

#include <uC++.h>
#include <uSemaphore.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "q1mapper.h"
#include "q1kvqueue.h"

using namespace std;

_Task Reducer {
  private:
    void main();
		int _id;
		int _num_reducers;
		uSemaphore* _signal;
		vector<Mapper*> _mappers;
		map<string,int> _keys;
		map<string,int>::iterator _it;


  public:
    Reducer(int id, int num_reducers, uSemaphore* signal,
            const vector<Mapper*>& mappers);
    virtual ~Reducer();

    // DJB2 hash. Include as part of the class interface.
    unsigned long hash(const string& str) {
        unsigned long hash = 5381;
        for (unsigned int i = 0; i < str.size(); ++i) {
            hash = ((hash << 5) + hash) + str[i];
        }
        return hash;
    }

    int getID();
    int getNumReducers();
    uSemaphore* getSignal();
    vector<Mapper*>& getMappers();
};

#endif 
