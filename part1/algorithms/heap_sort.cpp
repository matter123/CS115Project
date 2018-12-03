#include<iostream>
#include<vector>
#include "../sort_algo.h"
using namespace std;

int size = 0;

void heapify(int i, vector<int> &Arr, SortAlgorithm::Compare cmp) {
	int left = 2*i;
	int right = left +1;
	int largest = i;
	if (left <= size && !cmp(Arr.at(left),Arr.at(largest))) {
		largest = left;
	}

	if (right <= size && !cmp(Arr.at(right), Arr.at(largest))) {
		largest = right;
	}
	if (largest != i) {
		int temp = Arr.at(i);
		Arr.at(i) = Arr.at(largest);
		Arr.at(largest) = temp;
		heapify(largest, Arr, cmp);
	}
}

void heapSort(vector<int> &Arr, SortAlgorithm::Compare cmp) {	
	Arr.insert (Arr.begin(), 0);

	size = Arr.size()-1;
	for (size_t i = Arr.size()/2; i >= 1; i--) {
		heapify(i, Arr, cmp);
	}
	for (int i = size; i >= 2; i--) {
		int temp = Arr.at(i);
		Arr.at(i) = Arr.at(1);
		Arr.at(1) = temp;
		size--;
		heapify(1, Arr, cmp);
	}
		Arr.erase (Arr.begin());

}

SortAlgorithm HeapSort{"heap sort", heapSort};
