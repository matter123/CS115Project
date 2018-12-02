#include <utility>
#include "../in_set.h"
bool partition(std::vector<int> &arr, int val, InSetAlgorithm::Compare cmp) {
	using std::swap;
	if(arr.size() < 2) { return false; }
	auto mid = val / 2;
	// partition arr into two sub arrays
	//	1 containing all values less than 1/2 of val
	//	1 containing all values greater than 1/2 val
	//	if during the partition two values are found that are equal to 1/2 val and
	//	val is even return true, otherwise exactly equal to 1/2 val gets put into the
	//	partition of small values
	// compare each value of the first sub array with all the values of the second to
	// find a matching sum

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
	// partition = std::partition(first, last, [&](auto v) { return cmp(v, mid) <= 0;
	// });
	// subranges are now [first,partition) and [partition,last)
	while(first != partition) {
		auto loop = partition;
		while(loop != last) {
			if(cmp(*first + *loop, val) == 0) { return true; }
			++loop;
		}
		++first;
	}
	return false;
}

// InSetAlgorithm Partition{"partition", partition};
