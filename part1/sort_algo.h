#ifndef SORT_ALGO_H
#define SORT_ALGO_H
#include <chrono>
#include <functional>
#include <string>
#include <vector>
class SortAlgorithm {
  public:
	using Compare = std::function<bool(int, int)>;
	using FunctionType = std::function<void(std::vector<int> &, Compare)>;

  private:
	std::string name;
	FunctionType function;

  public:
	SortAlgorithm(std::string name, FunctionType func);
	std::chrono::nanoseconds timeAlgorithm(std::vector<int>, Compare c);
	std::string &getName() { return name; }
};
#endif
