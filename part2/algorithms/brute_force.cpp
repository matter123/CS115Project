#include <iostream>
#include "../in_set.h"
bool bruteForce(std::vector<int> &arr, int val, InSetAlgorithm::Compare cmp) {
	if(arr.size() < 2) { return false; }
	auto trailing = std::begin(arr);
	auto last = std::end(arr);
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
