#ifndef SORT_ALGO_H
#define SORT_ALGO_H
#include <chrono>
#include <functional>
#include <string>
#include <vector>

// Basically identical to SortAlgorithm from part1, but does not check for accuracy as it
// cannot know the answer, instead TestDriver looks for all algorithms to return the same
// result
class InSetAlgorithm {
  public:
	// Compare is spaceship operator +: lhs > rhs -: lhs < rhs 0: lhs == rhs
	using Compare = std::function<int(int, int)>;
	using FunctionType = std::function<bool(std::vector<int> &, int, Compare)>;

  private:
	std::string name;
	FunctionType function;

  public:
	InSetAlgorithm(std::string name, FunctionType func);
	std::chrono::nanoseconds timeAlgorithm(std::vector<int>, int, Compare,
	                                       bool &result);
	std::string &getName() { return name; }
};
#endif
