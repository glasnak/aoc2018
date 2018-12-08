#pragma once

// FIXME includes: less granularity
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <ostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "Coord.h"

struct Util {
  static std::vector<std::string> getLines(const std::string &Filename) {
    std::ifstream Infile(Filename);
    std::vector<std::string> Text;
    std::string Line;
    while (std::getline(Infile, Line)) {
      Text.emplace_back(Line);
    }
    return Text;
  }

  static std::vector<int> getNumbers(const std::string &Filename) {
    std::ifstream Infile(Filename);
    std::vector<int> Nums;
    std::string NumStr;
    while (Infile >> NumStr) {
      int Num = std::stoi(NumStr);
      Nums.emplace_back(Num);
    }
    return Nums;
  }

  static std::deque<char> getCharDeque(const std::string &Filename) {
    std::ifstream Infile(Filename);
    std::deque<char> Q;
    std::string Line;
    while (Infile >> Line) {
      for (char C : Line) {
        Q.emplace_back(C);
      }
    }
    return Q;
  }

  // from LLVM' STLExtras.h :
  template <typename R, typename E>
  static bool is_contained(R &&Range, const E &Element) {
    return std::find(std::begin(Range), std::end(Range), Element) !=
           std::end(Range);
  }

  // Comma-separated input of two numbers? int a, b; char c; while ((infile >> a
  // >> c >> b) && (c == ','))
  static std::vector<Coord> getCoord(const std::string &Filename) {
    std::ifstream Infile(Filename);
    std::vector<Coord> Result;
    std::string Line;
    int a, b;
    char c;
    while ((Infile >> a >> c >> b) && c == ',') {
      Result.emplace_back(Coord(a, b));
    }
    return Result;
  }
};
