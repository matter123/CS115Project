#include "sort_algo.h"
#include "test_driver.h"

#include <cassert>
#include <algorithm>
#include <iostream>
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
