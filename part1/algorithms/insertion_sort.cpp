#include <vector>
#include "../sort_algo.h"
using namespace std;


void insertionSort(vector<int> &list, SortAlgorithm::Compare cmp) {
	int key;
	int j;
	for(size_t i = 1; i < list.size(); i++) {
		key = list.at(i);
		j = i - 1;

		while(j >= 0 && !cmp(list.at(j), key)) {
			list.at(j + 1) = list.at(j);
			j--;
		}
		list.at(j + 1) = key;
	}
}

 SortAlgorithm InsertionSort{"insertion sort", insertionSort};
