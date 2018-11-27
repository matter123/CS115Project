#include <algorithm>
#include "../sort_algo.h"
SortAlgorithm StdSort{"std::sort", [](std::vector<int> &arr, SortAlgorithm::Compare cmp) {
	                      std::sort(arr.begin(), arr.end(), cmp);
                      }};
