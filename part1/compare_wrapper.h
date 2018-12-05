#ifndef COMPARE_WRAPPER_H
#define COMPARE_WRAPPER_H

#include <cstddef>
#include <functional>
#include <utility>


// wraps a comparsions functor and counts the number of times a comparisons is called
template <class T = int>
class CompareWrapper {
	size_t comparisons;
	std::function<bool(T, T)> cmp;

  public:
	CompareWrapper() = default;
	template <class Compare>
	CompareWrapper(Compare c) : cmp(c), comparisons(0){};
	constexpr bool operator()(T lhs, T rhs) {
		++comparisons;
		return cmp(std::forward<T>(lhs), std::forward<T>(rhs));
	}
	size_t getComparisons() { return comparisons; }
};

#endif
