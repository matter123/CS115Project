#include "in_set.h"
#include "test_driver.h"

#include <cassert>
#include <algorithm>
#include <iostream>
#include <iterator>

InSetAlgorithm::InSetAlgorithm(std::string _name, FunctionType func)
    : name(_name), function(func) {
	// register algorithm
	TestDriver::registerInSetAlgorithm(*this);
}
std::chrono::nanoseconds InSetAlgorithm::timeAlgorithm(std::vector<int> arr, int val,
                                                       Compare c, bool &result) {
	auto begin = std::chrono::high_resolution_clock::now();
	result = function(arr, val, c);
	auto end = std::chrono::high_resolution_clock::now();
	return end - begin;
}
