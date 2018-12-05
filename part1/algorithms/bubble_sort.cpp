#include <iostream>
#include <utility>
#include "../sort_algo.h"

//optimized version of bubble sort where it stops from further steps from 
//happening if there have not been any swaps in the previous pass
void bubbleSort(std::vector<int> &arr, SortAlgorithm::Compare cmp) {
	using std::swap;
	bool flag = false; //flag allows the function to be faster
	size_t end = arr.size();
	do {
		flag = false;
		for(size_t s = 1; s < end; s++) {
			if(cmp(arr.at(s), arr.at(s - 1))) {
				if(arr.at(s - 1) == arr.at(s)) { std::cerr << "duplicate"; }
				swap(arr.at(s - 1), arr.at(s));
				flag = true; //indicates that a swap occurred
			}
		}
		--end;
	} while(flag);
}

 SortAlgorithm BubbleSort{"bubble sort", bubbleSort};
