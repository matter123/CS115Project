#include <vector>
#include "../sort_algo.h"
using namespace std;

void selectionSort(vector<int> &list, SortAlgorithm::Compare cmp) {
	for(size_t i = 0; i < list.size(); i++) {
		int temp2 = i;
		for(size_t j = i; j < list.size(); j++) {
			if(!cmp(list.at(j), list.at(i))) { temp2 = j; }
		}
		swap(list.at(i), list.at(temp2));
	}
}
SortAlgorithm SelectionSort{"selection sort", selectionSort};
