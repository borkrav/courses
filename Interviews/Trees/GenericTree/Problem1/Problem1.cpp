// Problem1.cpp : Defines the entry point for the console application.
//

//genetic tree implementation, for practice

#include "stdafx.h"
#include <vector>

using namespace std;


class Node {

public:

	Node(vector<Node> children) {
		m_children = children;
	}

	Node() {
		vector<Node> empty;
		m_children = empty;
	}


	int getNumChildren(){
		return m_children.size();
	}

	Node getChild(int index) {
		return m_children[index];
	}

private:
	vector<Node> m_children;
};


class IntNode: public Node {

public:

	IntNode(int value) {
		m_value = value;
	}
		
	//call the base class constructor
	IntNode(vector<Node> children, int value) :Node(children) {
		m_value = value;
	}


private:
	int m_value;
};



//virtual class = compiler should use dynamic linkage = use member function of whatever the data is, rather than pointer type
// Shape* data = rect will use Shape's functions, rather than rectangle's functions, virtual avoids this

//pure virtual class = setting base class function to zero -> no implementation -> therefore base class is an interface, whatever classes inherit from it must have definitions for the pure virtual function

//abstract class is the same as an interface, which is the same as having a pure virtual function inside your class


int main()
{

	// a -> b c

	IntNode b(2);
	IntNode c(3);

	vector<Node> children;
	children.push_back(b);
	children.push_back(c);

	IntNode a(children, 1);


    return 0;
}

