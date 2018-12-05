#include "sort_algo.h"
#include "test_driver.h"

#include <cassert>
#include <algorithm>
#include <iostream>
#include <iterator>

// This class stores a name and a std::function object for each sorting algorithm
// The class auto-registers the algorithm with the test driver and provides a convenient
// way to time the sort algorithm
SortAlgorithm::SortAlgorithm(std::string _name, FunctionType func)
    : name(_name), function(func) {
	// register algorithm
	TestDriver::registerSortAlgorithm(*this);
}
std::chrono::nanoseconds SortAlgorithm::timeAlgorithm(std::vector<int> arr, Compare c) {
	// time algorithm
	auto begin = std::chrono::high_resolution_clock::now();
	function(arr, c);
	auto end = std::chrono::high_resolution_clock::now();
	// ensure the result is sorted, abort if not
	auto sorted = std::is_sorted(std::begin(arr), std::end(arr), c);
	if(!sorted) {
		std::cerr << name << ": ";
		std::cerr << (c(1, 0) ? " > " : " < ");
		for(auto elem : arr) { std::cerr << elem << " "; }
		std::cerr << std::endl;
		assert(sorted);
	}
	return end - begin;
}
