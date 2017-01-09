// Problem1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>

using namespace std;

class node {

private:
	node* m_left;
	node* m_right;
	int m_value;

public:

	node(node *left, node *right, int value) {
		m_left = left;
		m_right = right;
		m_value = value;
	}

	node* getLeft() {
		return m_left;
	}

	node* getRight() {
		return m_right;
	}

	int getValue() {
		return m_value;
	}


};

//recursive implementation of lookup
node* lookup(int value, node* root) {

	//base cases

	if (root == NULL) {
		return NULL;
	}

	if (root->getValue() == value) {
		return root;
	}

	//go right
	else if (root->getValue() < value){
		lookup(value, root->getRight());
	}
	//go left
	else if (root->getValue() > value) {
		lookup(value, root->getLeft());
	}



}

//preorder traversal of a BST
//visit yourself, visit left, visit right

//return nothing, upon visit, print
//no special cases. if root is null, it will return nothing
//runs on O(n) since we visit every node
void preorder(node* root) {

	//if null, do nothing
	if (root != NULL) {

		cout << root->getValue() << " ";

		preorder(root->getLeft());
		preorder(root->getRight());
	}

}


//non-recursive preorder traversal of a BST

//queue implementation to mimic recursion
//O(n) runtime, since we have to touch every node
//O(n) space for the vector, but using recursion is actually more expensive since gotta keep the call stack
//only error case is if root is NULL

void preorderNoRecurse(node* root) {

	if (root == NULL) {
		return;
	}

	vector<node*>nodes;

	//push on root
	nodes.push_back(root);

	while (nodes.size() != 0) {

		node* current = nodes.back();
		nodes.pop_back();

		cout << current->getValue() << " ";
		
		//push on right then left to maintain preorder
		if (current->getRight() != NULL) nodes.push_back(current->getRight());
		if (current->getLeft() != NULL) nodes.push_back(current->getLeft());

	}

}


//lowest common ancestor
//recursive solution
//exactly like lookup, but we're looking for a node such that a < n < b. this node has to be the lowest common ancestor due to properties of BSTs


//runtime is O(logn) since we're always picking one side of the tree to go down

//I'm lazy, so I'm just going to have it print the value once it finds it

void LCA(node* root, node* a, node* b) {

	//base case


	if (root == NULL) {
		return;
	}


	if (a->getValue() < root->getValue() && b->getValue() > root->getValue()) {
		cout << root->getValue() << endl;
	}

	else if (a->getValue() > root->getValue() && b->getValue() < root->getValue()) {
		cout << root->getValue() << endl;
	}

	
	else if (a->getValue() < root->getValue() && b->getValue() < root->getValue()) {
		LCA(root->getLeft(), a, b);
	}

	else if (a->getValue() > root->getValue() && b->getValue() > root->getValue()) {
		LCA(root->getRight(), a, b);
	}

}





int main()
{

	int s = 0;

	//    4
	// 2    6
	//1 3 5   7

	node n110(NULL, NULL, 110);
	node n25(NULL, NULL, 25);
	node n75(NULL, NULL, 75);
	node n125(&n110, NULL, 125);
	node n175(NULL, NULL, 175);
	node n50(&n25, &n75, 50);
	node n150(&n125, &n175, 150);
	node root(&n50, &n150, 100);

	//cout << lookup(100, &root) << endl;

	preorder(&root);

	cout << endl;

	preorderNoRecurse(&root);

	cout << endl;


	LCA(&root, &n75, &n25);
		
		

	cin >> s;

    return 0;
}

