#include "q1sortreducer.h"

void SortReducer::main(){

	//doneVect holds the status of all the mappers. 0 if not finished, 1 if finished
	vector<int> doneVect( getMappers().size());
	fill (doneVect.begin(),doneVect.end(),0);
	bool done = false;
	
	while (!done){
		
		bool gotOne = false;
		string smallest = "";

		//iterate over the mappers
		for (int i = 0; i < getMappers().size();){

			Mapper::KeyValue *val = new Mapper::KeyValue();			
		
			//if there's something in the queue
			if (getMappers()[i]->q->peekFront(val) == 0){
				
				//if the value is "I'm done", set it in the doneVect
				if (val->value == 0){
					gotOne = true;
					doneVect[i] = 1;
					i++;
				}
			
				//if the value belogs to the reducer, refresh the smallest key and insert
				//the value into the hash
				else if (hash (val->key) % getNumReducers() == getID()){
					
					if (i == 0) smallest = val->key;
					else if (val->key < smallest) smallest = val->key;

					_it = _keys.find(val->key);

					if (_it == _keys.end()){
						_keys.insert(pair<string,int>(val->key, val->value));
					}

					else if (_it != _keys.end()){
						_it->second += val->value;
					}
	
					getMappers()[i]->q->popFront();
					getSignal()->P();
					gotOne = true;
					i++;
				}
				//if there was nothing in the queue, yeild
				else {
					yield();
				}
			 
			}
			
			delete val;
		}

		
		//iterate over the hash, deleting and printing all the values smaller then the 			// smallest value found in the prevous scan over the queues
		_it = _keys.begin();
		string key;
		while (key != smallest){
			key = _it->first;
			int value = _it->second;

			osacquire( cout ) << key << " : " << value << endl;

			_keys.erase(_it++);

		}

		//check if all the mappers are done, if so exit
		bool result = true;
		for (int i = 0; i < doneVect.size(); i++){
			result = result && doneVect[i];
		}
		done = result;

	}



}


SortReducer::SortReducer(int id, int num_reducers, uSemaphore* signal,
            const vector<Mapper*>& mappers) : Reducer(id, num_reducers, signal, mappers){
}

SortReducer::~SortReducer(){

}
