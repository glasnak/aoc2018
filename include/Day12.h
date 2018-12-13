#pragma once

#include "Day.h"
#include <bitset>

class Day12 : public Day {
private:
  std::map<std::bitset<5>, bool> Rules;
  std::bitset<1000> Pots;
  void parseInput();
  int centralizePots();
  void advance();

public:
  Day12() : Day(12) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day12() override = default;
};
