#ifndef COMPARE_WRAPPER_H
#define COMPARE_WRAPPER_H

#include <cstddef>
#include <utility>

template <class Compare>
class CompareWrapper {
	size_t comparisons;
	Compare cmp;

  public:
	CompareWrapper(Compare c) : cmp(c), comparisons(0) = default;
	template <class T, class U>
	constexpr auto operator()(T &&lhs, U &&rhs)
	    -> decltype(cmp(std::forward<T>(lhs), std::forward<U>(rhs))) {
		++comparisons;
		return cmp(std::forward<T>(lhs), std::forward<U>(rhs));
	}
	size_t getComparisons() { return comparisons; }
};

#endif
