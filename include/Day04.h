#pragma once

#include "Day.h"
// #include <boost/algorithm/string.hpp>

class Day04 : public Day {
private:
  std::vector<std::string> Strings;
  std::map<int, std::vector<int>> Guards;
  std::map<int, int> Minutes;
public:
  Day04() : Day(4) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day04() override = default;
};
