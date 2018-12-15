#pragma once

#include "Day.h"
#include <bitset>

class Day12 : public Day {
private:
  // usage of bitset as a key to the map requires ability to compare them:
  struct BitsetComparer {
    bool operator()(const std::bitset<5> &b1, const std::bitset<5> &b2) const {
      return b1.to_ulong() < b2.to_ulong();
    }
  };
  std::map<std::bitset<5>, bool, BitsetComparer> Rules;
  std::bitset<1000> Pots;
  void parseInput();
  void advance();
  void printGeneration();
  long sumPlants();

  // part2
  int centralizePots();

public:
  Day12() : Day(12) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day12() override = default;
};
