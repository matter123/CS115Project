#ifndef TEST_DRIVER_H
#define TEST_DRIVER_H

#include <functional>
#include <vector>
#include "sort_algo.h"


class TestDriver {
	static std::vector<std::reference_wrapper<SortAlgorithm>> algorithms;
	using Generator =
	    std::function<void(std::vector<int> &, size_t, SortAlgorithm::Compare)>;

  public:
	static void registerSortAlgorithm(SortAlgorithm &);
	static void sortAlgorithms();
	static void testAlgorithms(double arraySizeExp, size_t trials, Generator g);
	// number source
	static void randomNumber(std::vector<int> &, size_t, SortAlgorithm::Compare c);
	static void partiallySorted(std::vector<int> &, size_t, SortAlgorithm::Compare c);
	static void sorted(std::vector<int> &, size_t, SortAlgorithm::Compare c);
};

#endif
