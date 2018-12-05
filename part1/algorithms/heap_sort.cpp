#include <iostream>
#include <vector>
#include "../sort_algo.h"

void heapify(int i, std::vector<int> &Arr, size_t size, SortAlgorithm::Compare cmp) {
	//gets left and right child of node to hepify
	int left = 2 * i;
	int right = left + 1;
	int largest = i;

	//sets largest/smallest(based on max or min sort) to the variable largest
	if(left <= size && !cmp(Arr.at(left), Arr.at(largest))) { largest = left; }
	if(right <= size && !cmp(Arr.at(right), Arr.at(largest))) { largest = right; }
	
	/*if the largest variable is not the passed in node then swap it with the proper 
	value to maintain heap property and calls heapify again on swapped value */
	if(largest != i) {
		int temp = Arr.at(i);
		Arr.at(i) = Arr.at(largest);
		Arr.at(largest) = temp;
		heapify(largest, Arr, size, cmp);
	}
}

void heapSort(std::vector<int> &Arr, SortAlgorithm::Compare cmp) {
	//adds 0 to begining of array to make heap opperations easier
	Arr.insert(Arr.begin(), 0);
	auto size = Arr.size() - 1;

	//builds a heap with the given array
	for(size_t i = Arr.size() / 2; i >= 1; i--) { heapify(i, Arr, size, cmp); }
	
	for(int i = size; i >= 2; i--) {
		int temp = Arr.at(i);
		Arr.at(i) = Arr.at(1);
		Arr.at(1) = temp;
		size--;
		heapify(1, Arr, size, cmp);
	}
	//remove 0 from front of array since sorting algorithm checks if array is sorted and would fail if it was a high to low sort. 
	Arr.erase(Arr.begin());
}

SortAlgorithm HeapSort{"heap sort", heapSort};
