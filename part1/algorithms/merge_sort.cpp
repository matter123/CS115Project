#include <cstdlib>
#include <vector>
#include "../sort_algo.h"
using namespace std;


void mergeSort(vector<int> &vec, SortAlgorithm::Compare cmp) {
	int left_pos = 0;
	int right_pos = 0;
	int pos = 0;
	if(vec.size() > 1) {
		vector<int> left(vec.begin(), vec.begin() + vec.size() / 2),
		    right(vec.begin() + vec.size() / 2, vec.end());

		mergeSort(left, cmp), mergeSort(right, cmp);

		while(left_pos < (int)left.size() && right_pos < (int)right.size()) {

			(cmp(left.at(left_pos), right.at(right_pos)))
			    ? (vec.at(pos++) = left.at(left_pos++))
			    : (vec.at(pos++) = right.at(right_pos++));

			if(left_pos == (int)left.size()) {
				while(right_pos < (int)right.size()) {
					vec.at(pos++) = right.at(right_pos++);
				}
			} else if(right_pos == (int)right.size()) {
				while(left_pos < (int)left.size()) {
					vec.at(pos++) = left.at(left_pos++);
				}
			}
		}
	}
}

// SortAlgorithm MergeSort{"merge sort", mergeSort};
