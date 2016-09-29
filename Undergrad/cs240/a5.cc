#include <iostream>
#include <vector>
using namespace std;

// Class to represent grid points.
class Point {
private:
	int lx, ly;
public:
	Point(int x = 0, int y = 0) { lx = x; ly = y; }
	int x() { return lx; }
	int y() { return ly; }
	
	void print(ostream &strm = cout)
	{
		strm << "(" << this->x() << "," << this->y() << ")";
	}
};

class HeapTree {
private:
	Point * lpPoint;
	HeapTree * lpLeftChild;
	HeapTree * lpRightChild;
	
public:
	HeapTree() {
		// Constructor
		lpPoint = NULL;
		lpLeftChild = NULL;
		lpRightChild = NULL;
	}
	
	~HeapTree() {
		// Deconstructor
		if (lpLeftChild != NULL) {
			delete lpLeftChild;
			lpLeftChild = NULL;
		}
		if (lpRightChild != NULL) {
			delete lpRightChild;
			lpRightChild = NULL;
		}
	}
	
	Point * pPoint() {
		// Returns the point stored at the root.  May return NULL, which
		// implies that the stored heap-tree is empty.
		return(lpPoint);
	}
	
	HeapTree * pLeftChild() {
		// Returns the root of left subtree; all points stored in it must have
		// x-coordinate >= pPoint.x() and y-coordinate <= yValue().
		// May return NULL if right subtree is empty.
		return(lpLeftChild);
	}
	
	HeapTree * pRightChild() {
		// Returns the root of right subtree; all points stored in it must have
		// x-coordinate >= pPoint.x() and y-coordinate >= yValue().
		// May return NULL if right subtree is empty.
		return(lpRightChild);
	}
	
	void print(ostream &strm, int indent = 0) {
		// Print the tree rooted at this node on the stream.   Uses an
		// indent and prints in inorder, so that the tree is quite visible
		// if you turn your head sideways.
		if (this->pPoint() != NULL) {
			// print right child first, indented more
			if (this->pRightChild() != NULL) {
				this->pRightChild()->print(strm, indent+5);
			}
			// print contents of root
			for (int i = 0; i < indent; i++) 
				strm << " ";
			this->pPoint()->print(strm);
 			strm << "[" << this->yValue() << "]\n";
			// print left child last, indented more
			if (this->pLeftChild() != NULL) {
				this->pLeftChild()->print(strm, indent+5);
			}
		}
	}
	
	int yValue(); 
	void insert(Point * pNewPoint);
	void query(int x, int y1, int y2, vector<Point*> & retVector);
	void buildFromScratch(const vector<Point*> & pointVector);
};

int HeapTree::yValue() {
	
	if (lpLeftChild == NULL && lpRightChild == NULL) {
		return lpPoint->y();
	}
	
	
	if (lpLeftChild == NULL) {
		Point * rPoint = lpRightChild->lpPoint;
		return rPoint->y();
	}

	else if (lpRightChild == NULL) {
		Point * lPoint = lpLeftChild->lpPoint;
		return lPoint->y();
	}
	
	else {
		Point * lPoint = lpLeftChild->lpPoint;
		int ly = lPoint->y();
		
		Point * rPoint = lpRightChild->lpPoint;
		int ry = rPoint->y();
		
		return min(ly, ry);
	}
	
}

void HeapTree::insert(Point * p) {
	// pre: No point with the same coordinates as p is in the HeapTree
	// post: p has been added to the HeapTree
	
	if (lpPoint == NULL) {
		lpPoint = p;
		
	}
	
	else {
		
		HeapTree * node = new HeapTree;
		node->lpPoint = p;
		
		HeapTree * posn = this;
		
		while ((posn->lpLeftChild != NULL && posn->lpRightChild != NULL) && p->x() > posn->lpPoint->x()) {
			
			if (p->y() <= posn->yValue()) {
				posn = posn->lpLeftChild;
				
			}
			
			else {
				posn = posn->lpRightChild;
			}
		}

		
		if (p->y() <= posn->yValue() && posn->lpLeftChild == NULL) {
			posn->lpLeftChild = node;
			
		}
		
		else if (p->y() > posn->yValue() && posn->lpRightChild == NULL) {
			posn->lpRightChild = node;
		}
		
/*
		else if (p->y() <= posn->yValue() && posn->lpLeftChild != NULL) {
			
			HeapTree * left = lpLeftChild;
			posn->lpLeftChild = node;
			
			if (left->yValue() <= p->y()) {
				node->lpLeftChild = left;
			}
			
			else {
				node->lpRightChild = left;
			}

			
			
		}
		
		else if (p->y() > posn->yValue() && posn->lpRightChild != NULL) {
			
			HeapTree * right = lpRightChild;
			posn->lpRightChild = node;
			
			if (right->yValue() <= p->y()) {
				node->lpLeftChild = right;
			}
			
			else {
				node->lpRightChild = right;
			}
			
		}
*/			
		
		
		
	}

	

	
	
	
	
}

void HeapTree::query(int x, int y1, int y2, vector<Point*> & retVector) {
	// pre: y1 <= y2, retVector is empty
	// post: retVector contains all points p in the heap-tree with p->x() <= x and
	//  y1 <= p->y() <= y2.  There is no particular order of points within 
	// the vector, but it contains each point only once.  The time for
	// this query is O(height + k), where k is the number of points in the output.
}

int compare(const void * a, const void * b){
	
	int c = ((Point*)a)->x();
	int d = ((Point*)b)->x();	
	return c-d;
	
}

void HeapTree::buildFromScratch(const vector<Point*> & pointVector) {
	// pre: pointVector contains at least one point.  this is an empty HeapTree
	// post: this stores all passed points and has height at most log(n).
	

	for (int i = 0 ; i < pointVector.size(); i++) {
		insert(pointVector[i]);
		
	}
	
}

#ifndef SCRIPTS
int main() 
{

}
#endif



