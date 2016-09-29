#include <uC++.h>
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;

_Task Searcher {

	public:
    struct Node {
        int key;
        string value;
        Node( int key, string value ) : key(key), value(value) {}
    };
    Searcher( list<Node> &multiset, int key, list<Node> &locns,
              unsigned int low, unsigned int high, list<Node>::iterator &start );
	
	private:

		void main();

		list<Node> *_multiset;
		int _key;
		list<Node> *_locns;
		unsigned int _low;
		unsigned int _high;
		list<Node>::iterator _start;


  
};
