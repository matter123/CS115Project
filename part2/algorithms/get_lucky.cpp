#include <utility>
#include "../in_set.h"


bool getLuckyPartition(std::vector<int> &arr, size_t first, size_t last, int pivot,
                       int val, InSetAlgorithm::Compare cmp) {
	using std::swap;
	while(first != last) {
		while(first < last && cmp(arr.at(first), pivot) < 0) first++;
		while(first < last && cmp(arr.at(last), pivot) >= 0) last--;
		if(cmp(arr.at(first) + arr.at(last), val) == 0) { return true; }
		swap(arr.at(first), arr.at(last));
	}
}

bool getLuckyQuicksort(std::vector<int> &arr, size_t first, size_t last, int val,
                       InSetAlgorithm::Compare cmp) {
	using std::swap;
	auto mid = first + (last - first) / 2;
	if(arr.at(mid) < arr.at(first)) { swap(arr.at(first), arr.at(mid)); }
	if(arr.at(last) < arr.at(first)) { swap(arr.at(first), arr.at(last)); }
	if(arr.at(mid) < arr.at(last)) { swap(arr.at(mid), arr.at(last)); }
	auto pivot = arr.at(last);
	if(getLuckyPartition(arr, first, last, pivot, val, cmp)) { return true; }
}


bool getLucky(std::vector<int> &arr, int val, InSetAlgorithm::Compare cmp) {
	using std::swap;
	if(arr.size() < 2) { return false; }
	auto mid = val / 2;

	auto first = std::begin(arr);
	auto partition = first;
	auto last = std::end(arr);

	// sort in ascending order
	try {
		std::sort(first, last, [&](auto a, auto b) {
			if(cmp(a + b, val) == 0) throw true;
			return cmp(a, b) <= 0;
		});
	} catch(bool b) { return b; }
	--last;
	while(first != last) {
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

InSetAlgorithm GetLucky{"getLucky", getLucky};
