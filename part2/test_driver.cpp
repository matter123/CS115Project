#include "test_driver.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include "compare_wrapper.h"

std::vector<std::reference_wrapper<InSetAlgorithm>> TestDriver::algorithms{};

void TestDriver::registerInSetAlgorithm(InSetAlgorithm &algo) {
	TestDriver::algorithms.emplace_back(algo);
}

void TestDriver::testAlgorithms(double arraySizeExp, size_t trials) {
	std::mt19937 rand{(unsigned int)time(nullptr)};
	std::uniform_int_distribution<int> uid{std::numeric_limits<int>::min() / 2,
	                                       std::numeric_limits<int>::max() / 2};
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
		if(choice(rand) || set.size() <= 2) {
			// most likely not a sum of two numbers in the set
			value = uid(rand);
		} else {
			std::uniform_int_distribution<int> pick(0, arraySize - 1);
			auto first = pick(rand);
			auto second = pick(rand);
			while(first == second) { second = pick(rand); }
			value = set[first] + set[second];
		}
		std::vector<bool> results;
		for(size_t algo = 0; algo < algorithms.size(); algo++) {
			bool result;
			CompareWrapper<int> cmp;
			times[algo].push_back(algorithms[algo].get().timeAlgorithm(
			    set, value, std::ref(cmp), result));
			comparisons[algo].push_back(cmp.getComparisons());
			results.push_back(result);
		}
		// confirm all algorithms got the same result
		if(!std::all_of(results.begin(), results.end(),
		                [&](auto v) { return v == *results.begin(); })) {
			std::cerr << "inconsistent results" << std::endl;
			for(auto s : set) { std::cerr << s << " "; }
			std::cerr << ", value:" << value << std::endl;
			for(size_t algo = 0; algo < algorithms.size(); algo++) {
				std::cerr << algorithms[algo].get().getName() << "\t"
				          << std::boolalpha << results[algo] << std::endl;
			}
			std::abort();
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
