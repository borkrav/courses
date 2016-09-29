#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
using namespace std;

class MinMaxHeap {
	
private:
	
	int heapSize;
	int levels;
    vector<int> heap;
	void swim(int k);
	
public:
	
	MinMaxHeap();
	~MinMaxHeap();
	
	void print();
	int size();
	void insert(int k);
	int getMin();
	int getMax();
	int levelOrderItem(int i);
	void changePriority(int i, int newPriority);
};

MinMaxHeap::MinMaxHeap() {
	// post: constructs an empty min-max heap
	heap.resize(1000);
	heap[0] = 'x';
	heapSize = 0;
}

MinMaxHeap::~MinMaxHeap() {
	// post: destructs the min-max heap
	heap.resize(0);
	heapSize = 0;
}

void MinMaxHeap::print() {
	//this is for debugging
	for (int i = 1; i <=heapSize; i++) {
		cout << heap[i] <<" ";
	}
	cout << endl;
}
	

int MinMaxHeap::size() {
	// post: returns the number of elements in the heap,
	// i.e., # calls to insert - # calls to deleteItemAtIndex
	return heapSize;
}

void MinMaxHeap::insert(int k) {
	// post: element k has been added to the min-max heap
	if (heapSize == 0){
		heap[1] = k;
		heapSize+=1;
	}
	
	else {
		heap[heapSize+1] = k;
		heapSize +=1;
		swim(heapSize);
	}

	
}	

int MinMaxHeap::getMin() {
	// pre: the heap is non-empty
	// post: returns the minimum value in O(1) time
	return heap[1];
}

int MinMaxHeap::getMax() {
	// pre: the heap is non-empty
	// post: returns the maximum value in O(1) time
	if (heapSize == 1) getMin();
	else if (heapSize < 2) return heap[2];
	else if (heap[2] > heap[3]) return heap[2];
	else if (heap[3] > heap[2]) return heap[3];
	else return 0;
}

int MinMaxHeap::levelOrderItem(int i) {
	// pre: 0 <= i < size()
	// post: returns the ith element of the min-max heap in level-order.
	// We count starting at 0, i.e., the root is the 0th item in level-order.
    return heap[i+1];
}

//a method for quicksort
int compare (const void * a, const void * b){
	return ( *(int*)a - *(int*)b );
}



void MinMaxHeap::swim(int x){
	
	//int compare (const void * a, const void * b){
	//	return ( *(int*)a - *(int*)b );
	//}
	
	
	levels = floor(log2(x));
	int parent = ceil(x/2);
	int gparent = ceil(parent/2);
	int swap = 0;
		
	int list[3];
	list[0]= heap[x];
	list[1]= heap[parent];
	list[2]= heap[gparent];
	
    qsort(list, 3, sizeof(int), compare);
	
	if (levels == 1 && heap[x] < heap[parent]){
		swap = heap[parent];
		heap[parent] = heap[x];
		heap[x] = swap;
	}
	
	else if (levels > 1){
		
		 if (levels%2 == 0){

			 heap[gparent] = list[0];
			 heap[x] = list[1];
			 heap[parent] = list[2];
			 swim(parent);
		 }
	
		 else if (levels%2 == 1){

			heap[parent] = list[0];
			heap[x] = list[1];
			heap[gparent] = list[2];
			swim(parent);
		}
	}	
}



void MinMaxHeap::changePriority(int i, int newPriority) {
	// pre: 0 <= i < size()
	// post: the item that was the ith item in level-order has its priority
	// changed to newPriority.   The heap is then changed to restore the heap
	// property.
	// This is a BONUS feature 
}


// Please leave the following line (and also the last line of the code)
// in place; this will allow our scripts to comment out the main routine
// and run correctly.
#ifndef SCRIPTS
int main() {
		
	MinMaxHeap heap;
	
	
	for (int i = 10; i >= 1; i--) {
		heap.insert(i);
	}
	
	
	heap.print();
	
	cout << heap.levelOrderItem(2)<<endl;
	cout << heap.size()<<endl;
	cout << heap.getMin()<<endl;
	cout << heap.getMax()<<endl;
	

	
}
#endif



