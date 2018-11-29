#ifndef COMPARE_WRAPPER_H
#define COMPARE_WRAPPER_H

#include <cstddef>
#include <functional>
#include <utility>

template <class T = int>
class CompareWrapper {
	size_t comparisons;
	std::function<int(T, T)> cmp;

  public:
	CompareWrapper() = default;
	template <class Compare>
	CompareWrapper(Compare c) : cmp(c), comparisons(0){};
	constexpr int operator()(T lhs, T rhs) {
		++comparisons;
		return cmp(std::forward<T>(lhs), std::forward<T>(rhs));
	}
	size_t getComparisons() { return comparisons; }
};

#endif
