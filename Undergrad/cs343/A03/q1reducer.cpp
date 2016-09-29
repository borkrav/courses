#include "q1reducer.h"

void Reducer::main(){

	//vector that holds values for whether or not a particular mapper is finished
	vector<int> doneVect( _mappers.size());
	fill (doneVect.begin(),doneVect.end(),0);
	bool done = false;
	
	while (!done){
		
		bool gotOne = false;

		//loop over all the mappers
		for (int i = 0; i < _mappers.size(); i++){


			Mapper::KeyValue *val = new Mapper::KeyValue();			
		
			//if there's something in the queue
			if (_mappers[i]->q->peekFront(val) == 0){
				
				//if it's the "I'm done" value, set it that in the doneVector
				if (val->value == 0){
					gotOne = true;
					doneVect[i] = 1;
				}
			
				//if it's not the done value and the key belongs to the reducer 
				//save the key on the hash
				else if (hash (val->key) % _num_reducers == _id){
					

					_it = _keys.find(val->key);

					if (_it == _keys.end()){
						_keys.insert(pair<string,int>(val->key, val->value));
					}

					else if (_it != _keys.end()){
						_it->second++;
					}
	
					_mappers[i]->q->popFront();
					_signal ->P();
					gotOne = true;
				}
			}
			delete val;
		}

		//if all queues proved to be empty, yield
		if (!gotOne) yield();	

		//scan over the done vector, and exit the loop if all values are 1
		bool result = true;
		for (int i = 0; i < doneVect.size(); i++){
			result = result && doneVect[i];
		}
		done = result;

	}


	//print out the hash
	for (_it = _keys.begin(); _it != _keys.end(); _it++){
		string key = _it->first;
		int value = _it->second;

		osacquire( cout ) << key << " : " << value << endl;
	}


}


Reducer::Reducer(int id, int num_reducers, uSemaphore* signal,
            const vector<Mapper*>& mappers){

		_id = id;
		_num_reducers = num_reducers;
		_signal = signal;
		_mappers = mappers;
}

Reducer::~Reducer(){

}

int Reducer::getID(){

	return _id;

}



int Reducer::getNumReducers(){

	return _num_reducers;

}

uSemaphore* Reducer::getSignal(){

	return _signal;

}

vector<Mapper*>& Reducer::getMappers(){

	return _mappers;

}
