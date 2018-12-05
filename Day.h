#pragma once
// Base class for all the Days.

#include "Util.h"

class Day {
protected:
  int Number;

public:
  explicit Day(int Num) : Number(Num) {}
  virtual void solvePart1() = 0;
  virtual void solvePart2() = 0;
  virtual ~Day() = default;
  // virtual ~Day() = 0;
  virtual void dump() const {
    std::cout << "\n--------------- Day #" << Number << "\n";
  }
  virtual void prettySolve() {
    dump();
    std::cout << "Part1:\t";
    solvePart1();
    std::cout << "Part2:\t";
    solvePart2();
  }
};
