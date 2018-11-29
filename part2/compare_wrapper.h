#ifndef COMPARE_WRAPPER_H
#define COMPARE_WRAPPER_H

#include <cstddef>
#include <functional>
#include <utility>

template <class T = int>
class CompareWrapper {
	size_t comparisons;

  public:
	CompareWrapper() = default;
	constexpr int operator()(T lhs, T rhs) {
		++comparisons;
		return lhs > rhs ? 1 : rhs > lhs ? -1 : 0;
	}
	size_t getComparisons() { return comparisons; }
};

#endif
