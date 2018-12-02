#include <cassert>
#include <algorithm>
#include <iostream>
#include <utility>
#include "../sort_algo.h"


// Hoare's partition scheme
template <class RandomIt>
RandomIt quickSortPartition(RandomIt first, RandomIt last, int pivot,
                            SortAlgorithm::Compare cmp) {
	using std::swap;
	auto i = first - 1;
	auto j = last + 1;
	while(true) {
		do { ++i; } while(cmp(*i, pivot));
		do { --j; } while(cmp(pivot, *j));
		if(i >= j) { return j; }
		swap(*i, *j);
	}
}

template <class RandomIt>
RandomIt medianOfThree(RandomIt first, RandomIt last, SortAlgorithm::Compare cmp) {
	using std::swap;
	auto mid = first + (last - first) / 2;
	if(!cmp(*mid, *first)) { swap(*mid, *first); }
	if(!cmp(*last, *first)) { swap(*last, *first); }
	if(!cmp(*mid, *last)) { swap(*mid, *last); }
	return last;
}

template <class RandomIt>
RandomIt first(RandomIt first, RandomIt last, SortAlgorithm::Compare cmp) {
	return first;
}

template <class RandomIt, class PivotFunc>
void quickSortImpl(RandomIt first, RandomIt last, SortAlgorithm::Compare cmp,
                   PivotFunc pivotfunc) {
	using std::swap;
	if(last - first < 1) { return; }
	if(last - first == 1) {
		if(cmp(*last, *first)) { swap(*first, *last); }
		return;
	}
	auto pivotValue = *pivotfunc(first, last, cmp);
	auto pivot1 = first;
	auto pivot2 = last;
	auto pivot = quickSortPartition(first, last, pivotValue, cmp);
	assert(pivot1 != pivot2);
	quickSortImpl(first, pivot, cmp, pivotfunc);
	if(!std::is_sorted(first, pivot1, cmp)) {
		std::cerr << "left part not sorted" << std::endl;
		std::cerr << "pivot is " << pivotValue << std::endl;
		while(first != pivot1) { std::cerr << *first++ << " "; }
		std::cerr << std::endl;
		std::cerr << "rest " << std::endl;
		while(first != last) { std::cerr << *first++ << " "; }
		std::cerr << std::endl;
		std::abort();
	}
	quickSortImpl(pivot + 1, last, cmp, pivotfunc);
	if(!std::is_sorted(pivot2, last, cmp)) {
		std::cerr << "right part not sorted" << std::endl;
		std::cerr << "pivot is " << pivotValue << std::endl;
		while(pivot2 != last) { std::cerr << *pivot2++ << " "; }
		std::cerr << std::endl;
		std::abort();
	}
}
/*
void quickSortMoT(std::vector<int> &arr, SortAlgorithm::Compare cmp) {
      quickSortImpl(arr.begin(), arr.end() - 1, cmp,
                    medianOfThree<typename std::vector<int>::iterator>);
}

SortAlgorithm QuickSortMot{"quick sort MoT", quickSortMoT};*/

void quickSortFirst(std::vector<int> &arr, SortAlgorithm::Compare cmp) {
	quickSortImpl(arr.begin(), arr.end() - 1, cmp,
	              first<typename std::vector<int>::iterator>);
}

SortAlgorithm QuickSortFirst{"quick sort first", quickSortFirst};
