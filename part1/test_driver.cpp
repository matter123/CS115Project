#include "test_driver.h"

#include <cmath>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include "compare_wrapper.h"

std::vector<std::reference_wrapper<SortAlgorithm>> TestDriver::algorithms{};

void TestDriver::registerSortAlgorithm(SortAlgorithm &algo) {
	TestDriver::algorithms.emplace_back(algo);
}
void TestDriver::testAlgorithms(double arraySizeExp, size_t trials) {

	std::mt19937 rand{(unsigned int)time(nullptr)};
	std::vector<std::vector<std::chrono::nanoseconds>> times(algorithms.size());
	std::vector<std::vector<size_t>> comparisons(algorithms.size());
	for(size_t t = 0; t < trials; t++) {
		size_t arraySize = std::pow(2, arraySizeExp);
		// around half of the trials will have an odd number of elements
		if(rand() % 2) { arraySize += 1; }
		// construct a test vector and fill with random numbers
		std::vector<int> trialVector;
		trialVector.reserve(arraySize);
		for(size_t s = 0; s < arraySize; s++) { trialVector.push_back(rand()); }
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
