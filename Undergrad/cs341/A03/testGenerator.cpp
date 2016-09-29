#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;


int main (int argc, char** argv){
    
    int argument = atoi(argv[1]);

    int testSize = argument * 3;
    
    cout << argument << endl;
    
    srand ( time(NULL) );
    
    vector <int> values;
    
    
    for (int i = 0; i < testSize; i++) {
        values.push_back(i);
    }
    
    
    int j = testSize;
    
    for (int i = 0; i < testSize; i+=3){
        int rand1 = rand() % j--;
        int val1 = values[rand1];
        values.erase(values.begin() + rand1);
        
        int rand2 = rand() % j--;
        int val2 = values[rand2];
        values.erase(values.begin() + rand2);
        
        int rand3 = rand() % j--;
        int val3 = values[rand3];
        values.erase(values.begin() + rand3);
        
        
        if (i % 2 == 0){
        
            
            
            
            cout << val1 << " " << min(val2, val3) << " " << val1 << " " << max(val2, val3) << endl;
        
        }
        
        else {
            
            cout << min(val1, val3) << " " << val2 << " " << max(val1, val3) << " " << val2 << endl;
            
        }
        
        
    }
    
    
    

    
    
    
    
    

}

