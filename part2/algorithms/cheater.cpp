#include <algorithm>
#include <limits>
#include <utility>

#include "../in_set.h"

bool cheater(std::vector<int> &arr, int val, InSetAlgorithm::Compare cmp) {
	if(val > std::numeric_limits<int>::max() / 2) { return true; }
	if(val < std::numeric_limits<int>::min() / 2) { return true; }
	using std::swap;
	if(arr.size() < 2) { return false; }
	auto mid = val / 2;

	auto first = std::begin(arr);
	auto partition = first;
	auto last = std::end(arr);
	// sort in ascending order
	std::sort(first, last, [&](auto a, auto b) { return cmp(a, b) <= 0; });
	--last;
	while(first <= last) {
		auto compare = cmp(*first + *last, val);
		if(compare == 0) { return true; }
		if(compare > 0) {
			--last;
		} else {
			++first;
		}
	}
	return false;
}

InSetAlgorithm Cheater{"cheater  ", cheater};
