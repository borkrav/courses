#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>


using namespace std;


int main (int argc, char** argv){
    
    int argument = atoi(argv[1]);

    cout << argument << endl;
 
	int testSize = argument * 2;

    srand ( time(NULL) );
   
    vector <int> values;
    
    
    for (int i = 0; i < testSize; i++) {
        values.push_back(i);
    }
    
	vector <pair <int, int> > theTest;

	for (int i = 0; i < argument; i++){
		theTest.push_back(make_pair(values[i], values[testSize-1-i]));
	}

	random_shuffle (theTest.begin(), theTest.end());

	theTest[0] = (make_pair (0,0));

	theTest[1] = (make_pair (testSize+1,testSize+1));
	
	for (int i = 0; i < argument; i++){
		cout << theTest[i].first << " " << theTest[i].second << endl;
	}


     

}

