#ifndef COMPARE_WRAPPER_H
#define COMPARE_WRAPPER_H

#include <cstddef>
#include <functional>
#include <utility>

// provides a countable three way comparison functor
// called ComparisonWrapper even though it does not wrap for parity with part1
template <class T = int>
class CompareWrapper {
	size_t comparisons{0};

  public:
	CompareWrapper() = default;
	// Compare is spaceship operator +: lhs > rhs -: lhs < rhs 0: lhs == rhs
	constexpr int operator()(T lhs, T rhs) {
		++comparisons;
		return lhs > rhs ? 1 : rhs > lhs ? -1 : 0;
	}
	size_t getComparisons() { return comparisons; }
};

#endif
