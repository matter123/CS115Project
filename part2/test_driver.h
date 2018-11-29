#ifndef TEST_DRIVER_H
#define TEST_DRIVER_H

#include <functional>
#include <vector>
#include "in_set.h"


class TestDriver {
	static std::vector<std::reference_wrapper<InSetAlgorithm>> algorithms;

  public:
	static void registerInSetAlgorithm(InSetAlgorithm &);
	static void testAlgorithms(double arraySizeExp, size_t trials);
};

#endif
