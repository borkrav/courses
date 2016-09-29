#include <uC++.h>
#include "q1sortmapper.h"
#include <iostream>
#include <fstream>

void SortMapper::main(){

	//check if the file can be opened
	if (access(getFilename().c_str(), F_OK) != 0 || access(getFilename().c_str(), R_OK) != 0){
			cerr << "Error opening file: " << getFilename() << endl;	
			exit(0);
	}

	
	while (true){

		//open the file
		fstream fin (getFilename().c_str(), fstream::in);
		string word;
		int counter = _buffer_size;

		map<string,int>::iterator it;
		set<string>::iterator set_it;

		while (fin >> word) {

			//check if I've seen this word already
			set_it = seenSoFar.find(word);

			//if I havent seen this word, and I'm still filling my initial hash
			//insert or update the entry in the hash
			if (counter > 0 && set_it == seenSoFar.end()){
				
				it = sortedBuffer.find(word);	
				
				if (it != sortedBuffer.end()){
					it->second++;
				}		

				else sortedBuffer.insert(pair<string,int>(word, 1));

				counter--;
			}

			//if I already filled my initial hash, and the next word is smaller then the 
			//biggest word in the hash, replace the next word with the biggest word
			else if (set_it == seenSoFar.end()) {

				it = sortedBuffer.find(word);
			
				if (it != sortedBuffer.end()){
					it->second++;
				}			
				else if (it == sortedBuffer.end()){
					it--;
					if (word < it->first){
						sortedBuffer.erase(it);
						sortedBuffer.insert(pair<string,int>(word, 1));
					}
				
				}

			}

		}

		//if nothing was inserted, then all the keys have already been processed
		if (sortedBuffer.size() == 0){
				break;
		}

		//push all the keys from the hash into the queue
		for (it = sortedBuffer.begin(); it != sortedBuffer.end(); it++){

			q->pushBack(KeyValue(it->first,it->second));		

			getSignal()->V();		

			seenSoFar.insert(it->first);
			

		}

		sortedBuffer.clear();

	}

	//push back the "I'm done" value
	q->pushBack(KeyValue("",0));	

}


SortMapper::SortMapper(const string& filename, int queue_len, int buffer_size, uSemaphore* signal) : Mapper(filename, queue_len, signal){	
	_buffer_size = buffer_size;
}

SortMapper::~SortMapper(){


}
