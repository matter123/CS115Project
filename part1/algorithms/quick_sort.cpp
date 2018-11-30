#include <algorithm>
#include <iostream>
#include <utility>
#include "../sort_algo.h"

/*
template<class RandomIt>
void quickSortPartition(RandomIt first, RandomIt)
*/

template <class RandomIt>
void quickSortImpl(RandomIt first, RandomIt last, SortAlgorithm::Compare cmp) {
	using std::swap;
	auto hi = last - 1; // quicksort is inclusive
	if(hi <= first) { return; }
	if(last - first == 2) {
		if(cmp(*hi, *first)) { swap(*first, *hi); }
		return;
	}
	// find median using median of three
	auto mid = first + (hi - first) / 2;
	if(cmp(*mid, *first)) { swap(*mid, *first); }
	if(cmp(*hi, *first)) { swap(*hi, *first); }
	if(cmp(*mid, *hi)) { swap(*mid, *hi); }
	//
	auto pivotValue = *hi;
	auto pivot =
	    std::partition(first, last, [&](auto v) { return !cmp(pivotValue, v); });
	quickSortImpl(first, pivot, cmp);
	quickSortImpl(pivot, last, cmp);
}

void quickSort(std::vector<int> &arr, SortAlgorithm::Compare cmp) {
	quickSortImpl(arr.begin(), arr.end() - 1, cmp);
}

SortAlgorithm QuickSort{"quick sort", quickSort};
