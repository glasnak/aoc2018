#pragma once

#include "Day.h"
#include "Matrix.h"

class Day11 : public Day {
private:
  const unsigned SerialNumber = 5535;
  const unsigned GridSize = 300;
  Matrix<long> Grid;
  constexpr void fillGrid(unsigned GridSize, unsigned SerialNumber);
  Matrix<long> sumGrid(unsigned SquareSize);

public:
  Day11() : Day(11) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day11() override = default;
};
