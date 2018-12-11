#pragma once

#include "Day.h"
#include <list>

class Day09 : public Day {
private:
  unsigned long play(unsigned NumPlayers, unsigned LastMarbleWorth,
                     unsigned WeirdestTurn = 23);

public:
  Day09() : Day(9) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day09() override = default;
};
