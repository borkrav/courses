#include <uC++.h>
#include "q1mapper.h"
#include "q1kvqueue.h"
#include <iostream>
#include <fstream>



void Mapper::main(){

	//first check if the file can be opened
	if (access(_filename.c_str(), F_OK) != 0 || access(_filename.c_str(), R_OK) != 0){
			cerr << "Error opening file: " << _filename << endl;	
			q->pushBack(KeyValue("",0));	
			exit(0);
	}

	
	fstream fin (_filename.c_str(), fstream::in);
	
	string word;

	//read the file
	while (fin >> word) {
	
		//push back every word wit count 1
		q->pushBack(KeyValue(word,1));		

		//signal that there's data available
		_signal->V();
	}

	//push back the "i'm done" value when the input runs out
	q->pushBack(KeyValue("",0));	

}


Mapper::Mapper(const string& filename, int queue_len, uSemaphore* signal){
	_filename = filename;
	_queue_len = queue_len;
	_signal = signal;

	q = new KVQueue(queue_len);

}

Mapper::~Mapper(){

	delete q;

}

uSemaphore* Mapper::getSignal(){
	return _signal;
}

const string& Mapper::getFilename(){
	return _filename;
}
