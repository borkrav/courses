// Problem1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <iostream>

using namespace std;

//first non-repeated charecter of a string


//brute force - for each letter, scan the string and search for duplicates. The first letter that has no duplicates is the result
//O(n^2) runtime

//the solution is to use a hashmap or an array - pretty lame...

//O(n) runtime since arrays have O(1) lookup

//edge cases - if the input string is length zero, return null

char firstNonRepeat(string input) {

	if (input.length() == 0) {
		return '\0';
	}

	int seenSoFar[256] = {0};


	string::iterator it = input.begin();

	//first scan, fill in seenSoFar array
	for (it; it != input.end(); it++) {
		seenSoFar[*it] += 1;
	}


	for (it = input.begin(); it != input.end(); it++) {
		if (seenSoFar[*it] == 1) return *it;
	}

	return '\0';


}





int main()
{

	char a;

	cout << firstNonRepeat("") << endl;

	cin >> a;

    return 0;
}

