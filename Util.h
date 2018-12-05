#pragma once

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

// FIXME: namespace instead of struct
struct Util {
  static std::vector<std::string> getLines(const std::string &Filename) {
    std::ifstream Infile(Filename);
    std::vector<std::string> Text;
    std::string Line;
    while (std::getline(Infile, Line)) {
      Text.push_back(Line);
    }
    return Text;
  }

  static std::vector<int> getNumbers(const std::string &Filename) {
    std::ifstream Infile(Filename);
    std::vector<int> Nums;
    std::string NumStr;
    while (Infile >> NumStr) {
      int Num = std::stoi(NumStr);
      Nums.push_back(Num);
    }
    return Nums;
  }

  static std::deque<char> getCharDeque(const std::string &Filename) {
    std::ifstream Infile(Filename);
    std::deque<char> Q;
    std::string Line;
    while (Infile >> Line) {
      for (char C : Line) {
        Q.push_back(C);
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
};
