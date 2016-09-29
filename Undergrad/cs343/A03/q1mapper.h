#ifndef _Q1MAPPER_H
#define _Q1MAPPER_H


#include <uC++.h>
#include <uSemaphore.h>
#include <string>


using namespace std;

class KVQueue;

_Task Mapper {
  private:
    void main();
		string _filename;
		int _queue_len;
		uSemaphore* _signal;

  public:
    struct KeyValue {
        string key;
        int value;

        KeyValue(const string& key, int value) : key(key), value(value) {}
        KeyValue() {}
    };

    Mapper(const string& filename, int queue_len, uSemaphore* signal);
    virtual ~Mapper();
    uSemaphore* getSignal();
    const string& getFilename();
    KVQueue* q;
};


#endif 
