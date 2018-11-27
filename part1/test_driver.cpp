#include "test_driver.h"
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <random>

std::vector<std::reference_wrapper<SortAlgorithm>> TestDriver::algorithms{};

void TestDriver::registerSortAlgorithm(SortAlgorithm &algo) {
	TestDriver::algorithms.emplace_back(algo);
}
void TestDriver::testAlgorithms(double arraySizeExp, size_t trials) {
	size_t arraySize = std::pow(2, arraySizeExp);

	std::mt19937 rand{(unsigned int)time(nullptr)};
	std::vector<std::vector<std::chrono::nanoseconds>> times(algorithms.size());
	for(size_t t = 0; t < trials; t++) {
		// construct a test vector and fill with random numbers
		std::vector<int> trialVector;
		if(rand() % 2) {
			trialVector.reserve(arraySize);
			for(size_t s = 0; s < arraySize; s++) { trialVector.push_back(rand()); }
		} else {
			// around half of the trials will have an odd number of elements
			trialVector.reserve(arraySize + 1);
			for(size_t s = 0; s < arraySize + 1; s++) {
				trialVector.push_back(rand());
			}
		}
		// have each algorithm sort a copy of the vector
		// making the copy can get expensive but it is not part of the time
		for(size_t algo = 0; algo < algorithms.size(); algo++) {
			times[algo].push_back(
			    algorithms[algo].get().timeAlgorithm(trialVector, std::less<>{}));
		}
	}
	// disply results;
	for(size_t algo = 0; algo < algorithms.size(); algo++) {
		std::chrono::nanoseconds avg =
		    std::accumulate(times[algo].begin(), times[algo].end(),
		                    std::chrono::nanoseconds{}) /
		    trials;
		std::chrono::duration<long double, std::milli> time = avg;
		std::cout << algorithms[algo].get().getName() << "\t" << arraySize << "\t"
		          << time.count() << std::endl;
	}
}
