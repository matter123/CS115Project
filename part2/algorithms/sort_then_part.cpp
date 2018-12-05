#include <algorithm>
#include <utility>
#include "../in_set.h"

// does a binary search for val or the smallest number greater than val
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
	// if there is only 1 or 0 elements there cannot be a sum of two
	if(arr.size() < 2) { return false; }
	// find partition value
	auto mid = val / 2;

	auto first = std::begin(arr);
	auto last = std::end(arr);
	// sort in ascending order
	std::sort(first, last, [&](auto a, auto b) { return cmp(a, b) <= 0; });
	// grab partition point
	auto partition = first;
	BST(first, last, mid, cmp, partition);
	--last;
	// loop until the two iterators reach eachother or one of the iterators reaches the
	// partition point the idea is that if the partition point is not in the middle of
	// of the set than this will be faster than waiting until they two iterators meet
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
