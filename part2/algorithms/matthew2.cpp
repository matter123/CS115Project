#include <utility>
#include "../in_set.h"
bool matthew2(std::vector<int> &arr, int val, InSetAlgorithm::Compare cmp) {
	using std::swap;
	if(arr.size() < 2) { return false; }
	auto mid = val / 2;
	// partition arr into two sub arrays
	//	1 containing all values less than 1/2 of val
	//	1 containing all values greater than 1/2 val
	//	if during the partition two values are found that are equal to 1/2 val and
	//	val is even return true, otherwise exactly equal to 1/2 val gets put into the
	//	partition of small values
	// sort the small value sub array in ascending order and the large value sub array
	// 	in descending order
	// compare each value of the small value sub array until the sum is smaller than val
	//	if the sum is larger than val remove the element from the large sub array

	bool foundExact = false;

	// Hoare partition scheme
	auto first = std::begin(arr);
	auto partition = first;
	auto last = std::end(arr);
	--last;
	while(partition != last) {
		// wait for inversion on partition
		while(partition != last) {
			auto compare = cmp(*partition, mid);
			if(compare == 0) {
				if(foundExact && !(val % 2)) { return true; }
				foundExact = true;
			}
			if(compare > 0) { break; }
			++partition;
		}
		// wait for inversion on last
		while(partition != last) {
			auto compare = cmp(*last, mid);
			if(compare == 0) {
				if(foundExact && !(val % 2)) { return true; }
				foundExact = true;
			}
			if(compare <= 0) { break; }
			--last;
		}
		swap(*partition, *last);
	}
	last = std::end(arr);
	// subranges are now [first,partition) and [partition,last)
	// sort them
	std::sort(first, partition, [&](auto a, auto b) { return cmp(a, b) <= 0; });
	std::sort(partition, last, [&](auto a, auto b) { return cmp(a, b) >= 0; });
	auto first1 = first;
	auto first2 = partition;
	auto last1 = partition;
	auto last2 = last;
	while(first1 != last1) {
		auto compare = cmp(*first1 + *first2, val);
		if(compare == 0) { return true; }
		if(compare > 0) {
			++first2;
			if(first2 == last2) { break; }
		} else {
			++first1;
		}
	}
	return false;
}

InSetAlgorithm Matthew2{"matthew(2)", matthew2};
