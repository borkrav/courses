// Class to implement sets of strings

// Implements operators for union, intersection, subtraction, 
//	etc. for sets of strings 

// V1.1 15 Feb 2011 Added guard (#ifndef), deleted using namespace RCH

#ifndef _STRSET_
#define _STRSET_

#include <iostream>
#include <string>
// Deleted: using namespace std;  15 Feb 2011 RCH

class strSet
{
private:
	
	struct node {
		std::string data;
		node * next;
	};
	
	node * first;

	
public:
	
    bool isSorted () const;
	
    strSet ();  // Create empty set
    strSet (std::string s); // Create singleton set
	strSet (const strSet &cp);
	
	void copyList(const strSet &cp);
	
    void nullify (); // Make a set be empty
    bool isNull () const;
    int SIZE() const;
	
    void output() const;
	
    bool isMember (std::string s) const;
	
    strSet  operator +  (const strSet& rtSide);  // Union
    strSet  operator *  (const strSet& rtSide);  // Intersection
    strSet  operator -  (const strSet& rtSide);  // Set subtraction
    strSet& operator =  (const strSet& rtSide);  // Assignment
	
};  // End of strSet class

#endif  // _STRSET_


