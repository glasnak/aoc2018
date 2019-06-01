#pragma once

#include "Day.h"

// a bit dangerous, not really an IS-A relationship:
struct Coord3D : public Coord {
  int z;
  Coord3D() : Coord(), z(0) {}
  Coord3D(const int &X, const int &Y, const int &Z) : Coord(X,Y), z(Z) {}

  Coord3D operator+(const Coord3D &other) const {
    return {x + other.x, y + other.y, z + other.z};
  }

  Coord3D operator-(const Coord3D &other) const {
    return {x - other.x, y - other.y, z - other.z};
  }

  // FIXME: doesn't override because it has a different return type, 
  //   so it hides it instead.
  Coord3D operator*(const int &multiplier) const {
    return Coord3D(x * multiplier, y * multiplier, z * multiplier);
  }

  // necessary for unordered_set comparison
  bool operator==(const Coord3D &other) const {
    return (x == other.x && y == other.y && z == other.z);
  }

  bool operator!=(const Coord3D &other) const {
    return !operator==(other);
  }

  // Necessary to use as a map key
  bool operator<(const Coord3D &rhs) const {
    if (x < rhs.x)
      return true;
    else if (x > rhs.x)
      return false;
    else if (y < rhs.y)
      return true;
    else if (y > rhs.y)
      return false;
    else
      return z < rhs.z;
  }

  // needed for unordered_set hashing
  size_t operator()(const Coord3D &ToHash) const noexcept {
    size_t
        hash = static_cast<unsigned>(ToHash.x + 137 * ToHash.y * 13 + ToHash.z);
    return hash;
  }

  void dump() const override {
    std::cout << "[" << x << "," << y << "," << z << "]\n"; 
  }
};


class Day23 : public Day {
  typedef std::vector<std::pair<Coord3D, int>> PointSet;
  PointSet Points;
  PointSet parse();

public:
  Day23() : Day(23) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day23() override = default;
};
