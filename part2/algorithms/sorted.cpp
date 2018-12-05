#include <algorithm>
#include <utility>
#include "../in_set.h"
bool sorted(std::vector<int> &arr, int val, InSetAlgorithm::Compare cmp) {
	using std::swap;
	if(arr.size() < 2) { return false; }
	auto mid = val / 2;

	auto first = std::begin(arr);
	auto partition = first;
	auto last = std::end(arr);
	// sort in ascending order
	std::sort(first, last, [&](auto a, auto b) { return cmp(a, b) <= 0; });
	--last;
	// if the two iterators reach eachother then every important combination has been
	// tried
	while(first <= last) {
		auto compare = cmp(*first + *last, val);
		if(compare == 0) { return true; }
		if(compare > 0) {
			// if the sum is too big decrement last so that the next time the sum is
			// smaller
			--last;
		} else {
			// otherwise the sum is too small so increment first so that the next
			// sum is bigger
			++first;
		}
	}
	return false;
}

InSetAlgorithm Sorted{"sorted  ", sorted};
