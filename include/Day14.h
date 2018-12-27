#pragma once

#include "Day.h"

class Day14 : public Day {
private:
  std::vector<int> Scoreboard;
  int Elf1, Elf2;
  void init();
  int fillScoreboard();
public:
  Day14() : Day(14) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day14() override = default;
};
