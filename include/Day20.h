#pragma once

#include "Day.h"
#include "Matrix.h"


class Day20 : public Day {
  Matrix<char> Grid;
  Matrix<int> DistanceGrid;
  std::vector<Coord> getAdjacentRooms(Coord Room);
  int search(Coord InitPosition, unsigned GridSize);
  void drawMap(const std::string &Regex, Coord InitPosition);
public:
  Day20() : Day(20) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day20() override = default;
};
