#include <utility>
#include "../sort_algo.h"

void bubbleSort(std::vector<int> &arr, SortAlgorithm::Compare cmp) {
	using std::swap;
	bool flag = false;
	size_t end = arr.size();
	do {
		flag = false;
		for(size_t s = 1; s < end; s++) {
			if(!cmp(arr.at(s - 1), arr.at(s))) {
				swap(arr.at(s - 1), arr.at(s));
				flag = true;
			}
		}
		--end;
	} while(flag);
}

SortAlgorithm BubbleSort{"bubble sort", bubbleSort};
