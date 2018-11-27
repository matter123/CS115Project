#ifndef TEST_DRIVER_H
#define TEST_DRIVER_H

#include <functional>
#include <vector>
#include "sort_algo.h"


class TestDriver {
	static std::vector<std::reference_wrapper<SortAlgorithm>> algorithms;

  public:
	static void registerSortAlgorithm(SortAlgorithm &);
	static void testAlgorithms(double arraySizeExp, size_t trials);
};

#endif
