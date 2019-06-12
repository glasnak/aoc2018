#pragma once

#include "Day.h"

struct Coord4D : public Coord {
  int z;
  int t;
  Coord4D() : Coord(), z(0), t(0) {}
  Coord4D(const int &X, const int &Y, const int &Z, const int &T)
      : Coord(X, Y), z(Z), t(T) {}

  int distance(const Coord4D &C) const {
    return abs(x - C.x) + abs(y - C.y) + abs(z - C.z) + abs(t - C.t);
  }
      
  void dump() const override {
    std::cout << "[" << x << "," << y << "," << z << "," << t << "]\n";
  }
};

class Day25 : public Day {
  
public:
  Day25() : Day(25) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day25() override = default;
};
