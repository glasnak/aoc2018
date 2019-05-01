#pragma once

#include "Day.h"
#include "Matrix.h"

class Day18 : public Day {

  Matrix<char> Grid;  // open ground (.), trees (|), lumberyard (#)
  void parse(const std::vector<std::string> &Lines);
  Matrix<char> step(const Matrix<char> &OldGrid);
public:
  Day18() : Day(18) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day18() override = default;
};
