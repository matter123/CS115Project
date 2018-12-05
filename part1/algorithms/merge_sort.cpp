#include <cstdlib>
#include <vector>
#include "../sort_algo.h"
using namespace std;


void mergeSort(vector<int> &vec, SortAlgorithm::Compare cmp) {
	int left_pos = 0;
	int right_pos = 0;
	int pos = 0;
	if(vec.size() > 1) {
		/* until the array size is one or less
			cut the vector in two halves and call mergeSort on them */
		vector<int> left(vec.begin(), vec.begin() + vec.size() / 2),
		    right(vec.begin() + vec.size() / 2, vec.end());

		mergeSort(left, cmp), mergeSort(right, cmp);

		//loop that runs until the left vector and right vector have both been fully itterated across
		while(left_pos < (int)left.size() && right_pos < (int)right.size()) {

			/*if sorting low to high and value at current left 
				vector index is greater than the current right vector
				then set the current sorted vector index to the value at left_pos
				and increment it by one. else do same thing but with right_pos*/
			(cmp(left.at(left_pos), right.at(right_pos)))
			    ? (vec.at(pos++) = left.at(left_pos++))
			    : (vec.at(pos++) = right.at(right_pos++));

			/*if the left vector has been itterated through already then add
				remaining right vector elements to the sorted array*/
			if(left_pos == (int)left.size()) {
				while(right_pos < (int)right.size()) {
					vec.at(pos++) = right.at(right_pos++);
				}
			}
			/*if the right vector has been itterated through already then add
				remaining left vector elements to the sorted array*/
			 else if(right_pos == (int)right.size()) {
				while(left_pos < (int)left.size()) {
					vec.at(pos++) = left.at(left_pos++);
				}
			}
		}
	}
}

 SortAlgorithm MergeSort{"merge sort", mergeSort};
