#ifndef TEST_DRIVER_H
#define TEST_DRIVER_H

#include <functional>
#include <vector>
#include "sort_algo.h"


class TestDriver {
	static std::vector<std::reference_wrapper<SortAlgorithm>> algorithms;

  public:
	static void registerSortAlgorithm(SortAlgorithm &);
	static void sortAlgorithms();
	template <class Generator>
	static void testAlgorithms(double arraySizeExp, size_t trials, Generator g);
	// number source
	template <class Compare>
	static void randomNumber(std::vector<int> &, size_t, Compare c);
	template <class Compare>
	static void partiallySorted(std::vector<int> &, size_t, Compare c);
	template <class Compare>
	static void sorted(std::vector<int> &, size_t, Compare c);
};

#endif
