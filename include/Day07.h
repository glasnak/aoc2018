#pragma once

#include "Day.h"
#include "Util.h"

class Day07 : public Day {
private:
  std::vector<std::pair<char, char>> Edges;
  std::set<char> Src, Dst;
  std::set<char> Letters;
  void init();
  std::vector<std::pair<char, char>> getInput();

public:
  Day07() : Day(7) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day07() override = default;
};
