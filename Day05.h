#pragma once

#include "Day.h"

class Day05 : public Day {
private:
  std::deque<char> Polymer;
  std::deque<char> reactPolymer(std::deque<char> PolymerQ);

public:
  Day05() : Day(5) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day05() override = default;
};
