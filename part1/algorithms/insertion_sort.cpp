#include <vector>
#include "../sort_algo.h"
using namespace std;


void insertionSort(vector<int> &list, SortAlgorithm::Compare cmp) {
	int key;
	int j;
	for(size_t i = 1; i < list.size(); i++) {
		key = list.at(i);
		j = i - 1;
		/* Move elements of list[0..i-1], that are 
          bigger than key, to  position right 
		  infront of their current position */
		while(j >= 0 && !cmp(list.at(j), key)) {
			list.at(j + 1) = list.at(j);
			j--;
		}
		list.at(j + 1) = key;
	}
}

 SortAlgorithm InsertionSort{"insertion sort", insertionSort};
