#ifndef SORT_ALGO_H
#define SORT_ALGO_H
#include <chrono>
#include <functional>
#include <string>
#include <vector>
class InSetAlgorithm {
  public:
	// Compare is spaceship operator +: lhs > rhs -: lhs < rhs 0: lhs == rhs
	using Compare = std::function<int(int, int)>;
	using FunctionType = std::function<void(std::vector<int> &, int, Compare)>;

  private:
	std::string name;
	FunctionType function;

  public:
	InSetAlgorithm(std::string name, FunctionType func);
	std::chrono::nanoseconds timeAlgorithm(std::vector<int>, int, Compare);
	std::string &getName() { return name; }
};
#endif
