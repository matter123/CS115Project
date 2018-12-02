#include <algorithm>
#include <iostream>
#include <utility>
#include "../sort_algo.h"


// Fat partition scheme
template <class RandomIt>
void quickSortPartition(RandomIt first, RandomIt last, int pivot,
                        SortAlgorithm::Compare cmp, RandomIt &p1, RandomIt &p2) {
	using std::swap;
	while(*first != pivot || *last != pivot) {
		while(first != last && cmp(*first, pivot)) { ++first; }
		while(first != last && cmp(pivot, *last)) { --last; }
		if(*first != pivot || *last != pivot) { swap(*first, *last); }
	}
	p1 = first;
	p2 = last;
}

template <class RandomIt>
void quickSortImpl(RandomIt first, RandomIt last, SortAlgorithm::Compare cmp) {
	using std::swap;
	if(last - first < 2) { return; }
	if(last - first == 2) {
		if(cmp(*last, *first)) { swap(*first, *last); }
		return;
	}
	// find median using median of three
	auto mid = first + (last - first) / 2;
	if(cmp(*mid, *first)) { swap(*mid, *first); }
	if(cmp(*last, *first)) { swap(*last, *first); }
	if(cmp(*mid, *last)) { swap(*mid, *last); }
	//
	auto pivotValue = *last;
	auto pivot1 = first;
	auto pivot2 = last;
	quickSortPartition(first, last, pivotValue, cmp, pivot1, pivot2);
	quickSortImpl(first, pivot1, cmp);
	quickSortImpl(pivot2, last, cmp);
}

void quickSort(std::vector<int> &arr, SortAlgorithm::Compare cmp) {
	quickSortImpl(arr.begin(), arr.end() - 1, cmp);
}

SortAlgorithm QuickSort{"quick sort", quickSort};
