#pragma once

#include "Day.h"
#include "Tree.h"
#include "Util.h"

class Day08 : public Day {
private:
  std::deque<int> NumQ;
  Tree<int> T;

public:
  Day08() : Day(8) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day08() override = default;
};
