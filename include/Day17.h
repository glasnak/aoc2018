#pragma once

#include "Day.h"
#include "Matrix.h"

class Day17 : public Day {

  Matrix<char> Grid;  // . is empty, # is wall, ~ is water, | is flowing water;
  std::vector<Coord> FlowingWater;

  void parse(const std::vector<std::string> &Lines);
  void flow();
  
public:
  Day17() : Day(17) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day17() override = default;
};
