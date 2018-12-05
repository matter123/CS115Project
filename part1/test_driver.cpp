#include "test_driver.h"

#include <cmath>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include "compare_wrapper.h"

// define the static vector of sorting algorithms
std::vector<std::reference_wrapper<SortAlgorithm>> TestDriver::algorithms{};


void TestDriver::registerSortAlgorithm(SortAlgorithm &algo) {
	// static function that registers a sort algorithm,
	// called by `SortAlgorithm`s
	TestDriver::algorithms.emplace_back(algo);
}

void TestDriver::sortAlgorithms() {
	// as automatic registration via constructors results in an undefined order
	// the sort algorithms need to be sorted according to their name
	std::sort(algorithms.begin(), algorithms.end(),
	          [](std::reference_wrapper<SortAlgorithm> lhs,
	             std::reference_wrapper<SortAlgorithm> rhs) {
		          return lhs.get().getName() < rhs.get().getName();
	          });
}
// a number source, provides randomly ordered numbers
void TestDriver::randomNumber(std::vector<int> &arr, size_t size,
                              SortAlgorithm::Compare c) {
	std::mt19937 rand{(unsigned int)time(nullptr)};
	std::uniform_int_distribution<int> uid(0, size - 1);
	for(size_t s = 0; s < size; s++) { arr.push_back(uid(rand)); }
}
// a number generation source, provides revese sorted numbers
void TestDriver::reverseSorted(std::vector<int> &arr, size_t size,
                               SortAlgorithm::Compare c) {
	TestDriver::sorted(arr, size, c);
	std::reverse(arr.begin(), arr.end());
}

// a number generation source, provides sorted numbers
void TestDriver::sorted(std::vector<int> &arr, size_t size, SortAlgorithm::Compare c) {
	randomNumber(arr, size, c);
	std::sort(arr.begin(), arr.end(), c);
}

// most important function in part1, calls all the algorithms, sets up the trials,
// and displays results
// @param arraySizeExp - the size of the test a = 2^N where N is arraySizeExp
// @param trials - the number of trials o perform
// @param g - the number generator used to fill the trial vector
void TestDriver::testAlgorithms(double arraySizeExp, size_t trials, Generator g) {
	std::mt19937 rand{std::random_device{}()};
	std::uniform_int_distribution<int> uid{std::numeric_limits<int>::min(),
	                                       std::numeric_limits<int>::max()};
	// stores time for each algorithm each trial
	std::vector<std::vector<std::chrono::nanoseconds>> times(algorithms.size());
	// stores the number of comparsions for each algorithm each trial
	std::vector<std::vector<size_t>> comparisons(algorithms.size());
	for(size_t t = 0; t < trials; t++) {
		size_t arraySize = std::pow(2, arraySizeExp);
		// around half of the trials will have an odd number of elements
		if(rand() % 2) { arraySize += 1; }
		// construct a test vector and fill with random numbers
		CompareWrapper<int> cmp{};
		// alternate the direction of the sort each trial
		cmp = t % 2 ? CompareWrapper<int>{std::less<>{}}
		            : CompareWrapper<int>{std::greater<>{}};
		std::vector<int> trialVector;
		// fill trial vector
		trialVector.reserve(arraySize);
		g(trialVector, arraySize, cmp);
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
		// average the times for each trial
		std::chrono::nanoseconds avgTime =
		    std::accumulate(times[algo].begin(), times[algo].end(),
		                    std::chrono::nanoseconds{}) /
		    trials;
		// .. and the number of comparsions
		size_t compCount = std::accumulate(comparisons[algo].begin(),
		                                   comparisons[algo].end(), size_t{}) /
		                   trials;
		// convert to milliseconds
		std::chrono::duration<long double, std::milli> time = avgTime;
		// display formatted
		std::cout << algorithms[algo].get().getName() << "\t" << std::setw(8)
		          << arraySize << "\t" << std::setprecision(7) << std::setw(12)
		          << std::fixed << time.count() << "\t" << std::setw(12) << compCount
		          << std::endl;
	}
}
