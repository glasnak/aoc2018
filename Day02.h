#pragma once

#include "Day.h"

class Day02 : public Day {
private:
  std::vector<std::string> Strings;
  const unsigned LineLength = 26;
  bool areNeighbours(const std::string One, const std::string Two);
  void printCommon(const std::string One, const std::string Two);
public:
  Day02() : Day(2) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day02() override {}
};
