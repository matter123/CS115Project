#include "../in_set.h"
bool bruteForce(std::vector<int> &arr, int val, InSetAlgorithm::Compare cmp) {
	if(arr.size() < 2) { return false; }
	auto trailing = std::begin(arr);
	auto last = std::end(arr);
	// given a set of {0,1,2,3,4,5}
	// this checks {(0,1), (0,2), (0,3), (0,4), (0, 5), (1,2), (1,3), (1,4), (1,5),
	// (2,3), (2,4), (2,5), (3,4), (3,5), (4,5)}
	// which is half you would expect from a true brute force approach
	// however addition is commutative so (1,0) and (0,1) are the same
	// see permutations vs combinations
	while(trailing != last) {
		auto leading = trailing + 1;
		while(leading != last) {
			int sum = *trailing + *leading;
			if(cmp(sum, val) == 0) { return true; }
			++leading;
		}
		++trailing;
	}
	return false;
}

InSetAlgorithm BruteForce{"brute force", bruteForce};
