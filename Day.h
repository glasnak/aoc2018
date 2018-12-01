#pragma once
// Base class for all the Days.

#include "Util.h"

class Day {
protected:
  int Number;
public:

  Day(int Num) : Number(Num) {}
  virtual void solvePart1() = 0;
  virtual void solvePart2() = 0;
  virtual ~Day() = default;
  // virtual ~Day() = 0;
  virtual void dump() const {
    std::cerr << "Day #" << Number << "\n";
  }
};


