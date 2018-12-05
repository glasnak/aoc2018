#pragma once
// On the first day of attempting to implement Advent of Code 2018, I have tried
// to do everything in C++. I was soon to be awakened to the reality of
// regretting this.

#include "Day.h"

class Day01 : public Day {
private:
  std::vector<int> Nums;
  // parent has Number and Inputs
public:
  Day01() : Day(1) {}
  void solvePart1() override;
  void solvePart2() override;
  // ~Day01() = default;
  ~Day01() override = default;
};
