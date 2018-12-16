#pragma once

#include "Day.h"
#include <bitset>
#include <unordered_map>

#define NUM_POTS 2000

class Day12 : public Day {
private:
  // usage of bitset as a key to the map requires ability to compare them:
  // struct BitsetComparer {
  //   bool operator()(const std::bitset<5> &b1, const std::bitset<5> &b2)
  //   const {
  //     return b1.to_ulong() < b2.to_ulong();
  //   }
  // };
  /// OR you can just use unordered_map ;)
  std::unordered_map<std::bitset<5>, bool> Rules;
  std::bitset<NUM_POTS> Pots;
  void parseInput();
  void advance();
  void printGeneration();
  long sumPlants(long Centralization = 0);

  // part2
  int centralizePots();

public:
  Day12() : Day(12) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day12() override = default;
};
