// Sorting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


void bubbleSort(vector<int> &data) {

	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data.size()-1; j++) {
			if (j + 1 < data.size() && data[j + 1] < data[j]) {
				int temp = data[j];
				data[j] = data[j+1];
				data[j + 1] = temp;
			}
		}
	}

}

void insertionSort(vector <int> &data) {

	for (int i = 0; i < data.size(); i++) {
		
		//d[i] is element we are inserting

		int j = i;

		//march back from i down to 0 until an element is smaller than d[i] - this is where we will insert d[i]
		while (j > 0 && data[i] < data[j - 1]) j--;

		int temp = data[i];

		//march from i down to j moving data one over
		for (int k = i; k > j; k--) {
			data[k] = data[k - 1];
		}

		//put data that was at i into j (the insert operation)
		data[j] = temp;



	}

}



int maximum_completed_tasks(int n, int t, const vector<int>& task_difficulties) {

	vector<int>sortedD = task_difficulties;

	sort(sortedD.begin(), sortedD.end());

	int count = 1;

	t = t - sortedD[0];

	if (t > 0) {

		for (int i = 1; i < n; i++) {

			t = t - sortedD[i] - abs(sortedD[i - 1] - sortedD[i]);

			if (t > 0) {
				count++;
			}
			else {
				return count;
			}

		}
	}

	else {
		return 0;
	}



}



int main()
{


	vector<int> data = { 18,  6,  9,  1,  4, 15, 12,  5,  6,  7, 11 };

	cout << maximum_completed_tasks(11, 50, data) << endl;

    return 0;
}

