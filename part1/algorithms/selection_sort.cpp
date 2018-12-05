#include <algorithm>
#include <vector>
#include "../sort_algo.h"
using namespace std;

void selectionSort(vector<int> &list, SortAlgorithm::Compare cmp) {
	//for loop to go through the list one time
	for(size_t i = 0; i < list.size(); i++) {
		//store the index we are currently at
		int temp2 = i;
		for(size_t j = i + 1; j < list.size(); j++) {
			/*for loop starts at value after one outer loop is in and compares each value of the rest of the 
			array with i and sets the lowest/highest value(high/low sort) to the temp*/
			if(cmp(list.at(j), list.at(temp2))) { temp2 = j; }
		}
		//swaps the current element with the lowest value from element greater than i
		swap(list.at(i), list.at(temp2));
	}
}
 SortAlgorithm SelectionSort{"selection sort", selectionSort};
