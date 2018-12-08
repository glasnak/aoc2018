#pragma once

#include "Coord.h"
#include "Day.h"
#include "Matrix.h"

class Day06 : public Day {
private:
  std::vector<Coord> Points;
  Matrix<int> M;
  void initMatrix(int Rows, int columns);
  void shiftPointsBy(int x, int y);
  int findClosest(Coord Cell);
  std::map<int, int> countCells();

public:
  Day06() : Day(6) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day06() override = default;
};
