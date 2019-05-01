#pragma once

#include "Day.h"
#include "Matrix.h"

class Day19 : public Day {
  void parse(const std::vector<std::string> &Lines);
public:
  Day19() : Day(19) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day19() override = default;
};
