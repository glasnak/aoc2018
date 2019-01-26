#pragma once

#include <cstddef>  // size_t
#include <iostream> // cout
#include <vector>   // Move

enum /*class*/ Direction {
  NORTH,
  EAST,
  SOUTH,
  WEST,
  INVALID
};
                                          // N,E,S,W movement:
const std::vector<std::pair<int, int>> Move{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct Coord {
  int x;
  int y;

  Coord() : x(0), y(0) {}
  Coord(const int &X, const int &Y) : x(X), y(Y) {}

  // necessary for unordered_set comparison
  bool operator==(const Coord &other) const {
    return (x == other.x && y == other.y);
  }
  
  // Necessary to use as a map key
  bool operator<(const Coord &rhs) const { // reversed x,y?
    if (x < rhs.x)
      return true;
    else if (x > rhs.x)
      return false;
    else
      return y < rhs.y;
  }

  // needed for unordered_set hashing
  size_t operator()(const Coord &ToHash) const noexcept {
    size_t hash = static_cast<unsigned>(ToHash.x + 137 * ToHash.y);
    return hash;
  }

  void dump() const { std::cout << "[" << x << "," << y << "]\n"; }
};