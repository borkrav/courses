#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;


class HashTable {
	
public:
	HashTable();
	~HashTable();
	
	vector<string> table;
	int iterations;
	bool loop;
	
	int numItems();
	int size();
	void insert(string s);	
	int search(string s);	
	void deleteIfIn(string s);	
	int initialSize();
	int nextSize(int currentSize);
	int hashValue(string s, bool primary, int currentSize);
	bool needsRehashing();
	
	string stringAtIndex(int i); 
	
	bool permuteTester(const char * file1, const char * file2);
};

HashTable::HashTable() {
	// post: constructs an empty hash table
	table.resize(initialSize());
	
	for (int i = 0; i<initialSize(); i++) {
		table[i] = "";
	}
	
}

HashTable::~HashTable() {
	// post: destructs the hash table
	table.resize(0);
}

int HashTable::numItems() {
	// post: returns the number of items that are stored in the hash table.
	int counter;
	
	for (int i = 0; i <size(); i++) {
		if (table[i] != "NULL SPACE") {
			counter++;
		}
	}
	
	
	return counter; // return your numItems here
}

int HashTable::size() {
	// post: returns the size that the hash table has.  
	return table.size(); // return your size here
}

int HashTable::initialSize() {
	// post: returns the size that is used in the hash table initially.
	
	return 1;
#ifdef DISCUSSION
	I decided to change the standard approach because ...
#endif
}

int HashTable::nextSize(int currentSize) {
	// pre: currentSize was obtained via 
	//	nextSize(nextSize(nextSize(...(nextSize(initialSize())
	// post: returns the next size that will be tried for the hash table if
	// the current size is currentSize.   The next size must be bigger than
	// currentSize.
	
	// NOTE: You are welcome to add a convention such as if you pass -1 to
	// "currentSize", then the current size of the hash table is used.  We
	// won't be using this feature, but you might want to add it to simplify
	// your code.  A similar note holds for all other methods that pass 
	// currentSize or currentNumItems.
	
	return  2 * currentSize;
#ifdef DISCUSSION
	I decided to change the standard approach because ...
#endif
}

int HashTable::hashValue(string s, bool primary, int currentSize) {
	// pre: s is a non-empty string. currentSize was obtained via 
	//	nextSize(nextSize(nextSize(...(nextSize(initialSize())
	// post: returns the hash value used for the primary (if primary == true)
	// or secondary (if primary == false) hash function if the table size is 
	// currentSize.  This return value is between 0 and currentSize-1.
	
	if (primary) {
		
		double value = 0;
		double b = currentSize % 7;
		
		for (int i = 0; i < s.length(); i++) {
			value += (int)s[i] * pow(b, s.length()-i);
		}
		
		cout << value << endl;
		
		
		value = fmod(value, (double)currentSize);
		
		return (int)value;
	}
	
	else {
		
		double value = 0;
		double b = currentSize % 13;
		
		for (int i = 0; i < s.length(); i++) {
			value += (int)s[i] * pow(b, s.length()-i);
		}
		
		cout << value << endl;
		
		
		value = fmod(value, (double)currentSize);
		
		return (int)value;
	}
	
	
	
	
 // return your value here
	
	
#ifdef DISCUSSION
	I used the following approach for computing the hash-functions:
		...
		
		The reason I chose these hash-functions is:
		...
#endif
		}


bool HashTable::needsRehashing() {
	// post: returns whether re-hashing should be done 
	
	return (numItems() > (size() / 4));
#ifdef DISCUSSION
	I decided to change the standard approach because ...
#endif
}

void HashTable::insert(string s) {
	// pre: s is a non-empty string that is not in the hash-table.
	// post: s has been added to the hash table.   The hash table
	// may have increased in size.
	if (needsRehashing() || loop) {
		
		vector<string>newTable;
		newTable.resize(nextSize(size()));
		
		for (<#initial#>; <#condition#>; <#increment#>) {
			<#statements#>
		}
		
		
	}
	
	int primary = hashValue(s, true, size());
	int secondary = hashValue(s, false, size());
	
	if (table[primary] == "") {
		table[primary] = s;
	}
	
	else {
		insert(table[primary]);
		table[primary] = s;
	}

	iterations +=1;
	
	if (iterations >= size()) {
		loop = true;
	}
	
	
	
	
}

int HashTable::search(string s) {
	// pre: s is a non-empty string that is in the hash-table at most once.
	// post: returns index where s is stored if s is in the hash-table.  Returns
	// -1 if s is not in the hash-table.
	return -1; // return your search result here
}

void HashTable::deleteIfIn(string s) {
	// pre: s is a non-empty string that is in the hash-table at most once.
	// post: if s is in the hash-table, it gets deleted.  Otherwise the hash
	// table is unchanged.
}

string HashTable::stringAtIndex(int i) {
	// post: returns the string stored at slot i of the hash table
	return ""; // return your string here
}

bool HashTable::permuteTester(const char * file1, const char * file2) {
	// pre: <file1> and <file2> exist and contains only words over the
	// alphabet a-z, plus one word `#' at the end.   Each file has no duplicates.
	// post: returns true if the two files contain the same set of words
	return false; // return your result here
}

#ifndef SCRIPTS
int main() {
	
	
	return 0;
}
#endif
