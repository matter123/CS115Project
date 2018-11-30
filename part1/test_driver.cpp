#include "test_driver.h"

#include <cmath>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include "compare_wrapper.h"

std::vector<std::reference_wrapper<SortAlgorithm>> TestDriver::algorithms{};


void TestDriver::registerSortAlgorithm(SortAlgorithm &algo) {
	TestDriver::algorithms.emplace_back(algo);
}

void TestDriver::sortAlgorithms() {
	std::sort(algorithms.begin(), algorithms.end(),
	          [](std::reference_wrapper<SortAlgorithm> lhs,
	             std::reference_wrapper<SortAlgorithm> rhs) {
		          return lhs.get().getName() < rhs.get().getName();
	          });
}

void TestDriver::randomNumber(std::vector<int> &arr, size_t size) {
	std::mt19937 rand{(unsigned int)time(nullptr)};
	std::uniform_int_distribution<int> uid{std::numeric_limits<int>::min(),
	                                       std::numeric_limits<int>::max()};
	for(size_t s = 0; s < size; s++) { arr.push_back(uid(rand)); }
}


template <class Generator>
void TestDriver::testAlgorithms(double arraySizeExp, size_t trials, Generator g) {

	std::mt19937 rand{(unsigned int)time(nullptr)};
	std::uniform_int_distribution<int> uid{std::numeric_limits<int>::min(),
	                                       std::numeric_limits<int>::max()};
	std::vector<std::vector<std::chrono::nanoseconds>> times(algorithms.size());
	std::vector<std::vector<size_t>> comparisons(algorithms.size());
	for(size_t t = 0; t < trials; t++) {
		size_t arraySize = std::pow(2, arraySizeExp);
		// around half of the trials will have an odd number of elements
		if(rand() % 2) { arraySize += 1; }
		// construct a test vector and fill with random numbers
		std::vector<int> trialVector;
		trialVector.reserve(arraySize);
		g(trialVector, arraySize);
		// have each algorithm sort a copy of the vector
		// making the copy can get expensive but it is not part of the time
		for(size_t algo = 0; algo < algorithms.size(); algo++) {
			CompareWrapper<int> cmp{};
			// alternate the direction of the sort each trial
			cmp = t % 2 ? CompareWrapper<int>{std::less<>{}}
			            : CompareWrapper<int>{std::greater<>{}};
			times[algo].push_back(
			    algorithms[algo].get().timeAlgorithm(trialVector, std::ref(cmp)));
			// std::is_sorted performs N comparisons, so subtract them
			comparisons[algo].push_back(cmp.getComparisons() - (arraySize - 1));
		}
	}
	// disply results;
	size_t arraySize = std::pow(2, arraySizeExp);
	for(size_t algo = 0; algo < algorithms.size(); algo++) {
		std::chrono::nanoseconds avgTime =
		    std::accumulate(times[algo].begin(), times[algo].end(),
		                    std::chrono::nanoseconds{}) /
		    trials;
		size_t compCount = std::accumulate(comparisons[algo].begin(),
		                                   comparisons[algo].end(), size_t{}) /
		                   trials;
		std::chrono::duration<long double, std::milli> time = avgTime;
		std::cout << algorithms[algo].get().getName() << "\t" << std::setw(5)
		          << arraySize << "\t" << std::setprecision(7) << std::setw(12)
		          << std::fixed << time.count() << "\t" << std::setw(12) << compCount
		          << std::endl;
	}
}
