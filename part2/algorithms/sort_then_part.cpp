#include <utility>
#include "../in_set.h"
bool sortThenPart(std::vector<int> &arr, int val, InSetAlgorithm::Compare cmp) {
	using std::swap;
	if(arr.size() < 2) { return false; }
	auto mid = val / 2;

	auto first = std::begin(arr);
	auto last = std::end(arr);
	// sort in ascending order
	std::sort(first, last, [&](auto a, auto b) { return cmp(a, b) <= 0; });
	// grab partition point
	auto partition =
	    std::partition_point(first, last, [&](auto v) { return cmp(v, mid) <= 0; });
	--last;
	while(first != last && first != partition) {
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

InSetAlgorithm SortThenPart{"sort then part", sortThenPart};
