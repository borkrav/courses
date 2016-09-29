// File strset3.h

// Class to implement sets of strings

// Implements operators for union, intersection, subtraction, 
//	etc. for sets of strings 

#ifndef STRSET_H
#define STRSET_H

#include <iostream>
#include <vector>
#include <string>

class strSet
{
protected:  // changed this from private
    struct myNode
    {
        std::string str;
        myNode * next;
	myNode (std::string s, myNode * p)
	    : str (s), next (p) 
	{ // No body
	}
    };

    myNode * first;

    bool isSorted () const;

public:
    strSet ();  // Create empty set
    strSet (std::string s); // Create singleton set

    void nullify (); // Make a set be empty
    bool isNull () const;
    int SIZE() const;

    void output() const;

    bool isMember (std::string s) const;

    strSet  operator +  (const strSet& rtSide);  // Union
    strSet  operator *  (const strSet& rtSide);  // Intersection
    strSet  operator -  (const strSet& rtSide);  // Set subtraction
    strSet& operator =  (const strSet& rtSide);  // Assignment

    strSet (const strSet& rtSide); // Copy constructor
    ~strSet ( );  // Destructor
};  // End of strSet class

#endif
