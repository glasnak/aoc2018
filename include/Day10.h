#pragma once

#include "Coord.h"
#include "Day.h"
#include "Util.h"

class Day10 : public Day {
private:
  // In need of a structure to hold "position=<-3, 11> velocity=< 1, -2>"
  std::vector<Coord> Positions;
  std::vector<Coord> Velocities;
  // These will be used to populate sparse matrix representing Light in the sky:
  std::map<int, std::set<int>> Lights;

  void parseInput();
  void updateLights();
  void printMessage();
  void tick();

public:
  Day10() : Day(10) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day10() override = default;
};
