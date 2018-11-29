#include "test_driver.h"
#include <cstdlib>
#include <iostream>
#include <random>
#include "compare_wrapper.h"

std::vector<std::reference_wrapper<InSetAlgorithm>> TestDriver::algorithms{};

void TestDriver::registerInSetAlgorithm(InSetAlgorithm &algo) {
	TestDriver::algorithms.emplace_back(algo);
}

void TestDriver::testAlgorithms(double arraySizeExp, size_t trials) {
	std::mt19937 rand{(unsigned int)time(nullptr)};
	std::uniform_int_distribution<int> uid{std::numeric_limits<int>::min(),
	                                       std::numeric_limits<int>::max()};
	std::uniform_int_distribution<int> choice{0, 1};
	std::vector<std::vector<std::chrono::nanoseconds>> times(algorithms.size());
	std::vector<std::vector<size_t>> comparisons(algorithms.size());
	for(size_t t = 0; t < trials; t++) {
		size_t arraySize = std::pow(2, arraySizeExp);
		// around half of the trials will have an odd number of elements
		if(choice(rand)) { arraySize += 1; }
		// construct a test vector and fill with random numbers
		std::vector<int> set;
		set.reserve(arraySize);
		for(size_t s = 0; s < arraySize; s++) { set.push_back(uid(rand)); }
		int value;
		if(choice(rand)) {
			// most likely not a sum of two numbers in the set
			value = uid(rand);
		} else {
			std::uniform_int_distribution<int> pick{0, arraySize - 1};
			auto first = pick(rand);
			auto second = pick(rand);
			while(first == second) { second = pick(rand); }
			value = set[first] + set[second];
		}
		std::vector<bool> results;
		for(size_t algo = 0; algo < algorithms.size(); algo++) {
			bool result;
			CompareWrapper<int> cmp;
			times[algo].push_back(
			    algorithms[algo].get().timeAlgorithm(set, value, cmp, result));
			comparisons[algo].push_back(cmp.getComparisons());
			results.push_back(result);
		}
		// confirm all algorithms got the same result
		if(!std::all_of(results.begin(), results.end(),
		                [&](auto v) { v == *results.begin() })) {
			std::cerr << "inconsistent results" << std::endl;
			for(size_t algo = 0; algo < algorithms.size(); algo++) {
				std::cerr << algorithms[algo].get().getName() << "\t"
				          << results[algo] << std::endl;
				std::abort();
			}
		}
	}
