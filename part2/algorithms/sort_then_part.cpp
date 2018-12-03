#include <algorithm>
#include <utility>
#include "../in_set.h"

template <class RandomIt>
bool BST(RandomIt first, RandomIt last, int val, InSetAlgorithm::Compare c,
         RandomIt &ret) {
	RandomIt too_low = first;
	RandomIt too_high = last;
	while((too_low + 1) < too_high) {
		RandomIt check = too_low + (too_high - too_low) / 2;
		int cmp = c(val, *check);
		if(!cmp) {
			ret = check;
			return true;
		}
		if(cmp > 0) {
			too_low = check;
		} else {
			too_high = check;
		}
	}
	ret = too_high;
	return false;
}

bool sortThenPart(std::vector<int> &arr, int val, InSetAlgorithm::Compare cmp) {
	using std::swap;
	if(arr.size() < 2) { return false; }
	auto mid = val / 2;

	auto first = std::begin(arr);
	auto last = std::end(arr);
	// sort in ascending order
	std::sort(first, last, [&](auto a, auto b) { return cmp(a, b) <= 0; });
	// grab partition point
	auto partition = first;
	BST(first, last, mid, cmp, partition);
	--last;
	while(first != last && first != partition && last != (partition - 1)) {
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
