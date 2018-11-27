#include "sort_algo.h"
#include "test_driver.h"

#include <cassert>
#include <algorithm>
#include <iterator>

SortAlgorithm::SortAlgorithm(std::string _name, FunctionType func)
    : name(_name), function(func) {
	// register algorithm
	TestDriver::registerSortAlgorithm(*this);
}
std::chrono::nanoseconds SortAlgorithm::timeAlgorithm(std::vector<int> arr, Compare c) {
	auto begin = std::chrono::high_resolution_clock::now();
	function(arr, c);
	auto end = std::chrono::high_resolution_clock::now();
	assert(std::is_sorted(std::begin(arr), std::end(arr), c));
	return end - begin;
}
