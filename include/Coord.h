#pragma once

#include <cstddef>  // size_t
#include <iostream> // cout

enum /*class*/ Direction {
  NORTH = 0,
  EAST,
  SOUTH,
  WEST
};

struct Coord {
  int x;
  int y;

  Coord() : x(0), y(0) {}
  Coord(const int &X, const int &Y) : x(X), y(Y) {}

  // necessary for unordered_set comparison
  bool operator==(const Coord &other) const {
    return (x == other.x && y == other.y);
  }

  // needed for unordered_set hashing
  size_t operator()(const Coord &ToHash) const noexcept {
    size_t hash = static_cast<unsigned>(ToHash.x + 137 * ToHash.y);
    return hash;
  }

  void dump() const { std::cout << "[" << x << "," << y << "]\n"; }
};