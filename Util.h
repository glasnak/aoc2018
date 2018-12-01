#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>

struct Util {
  // With a comma, you'd say: int a, b; char c; while ((infile >> a >> c >> b) && (c == ','))
  static std::vector<std::string> getLines(std::string Filename) {
    std::ifstream Infile(Filename);
    std::vector<std::string> Text;
    std::string Line = "";
    while (std::getline(Infile, Line)) {
      Text.push_back(Line);
    }
    return Text;
  }

  static std::vector<int> getNumbers(std::string Filename) {
    std::ifstream Infile(Filename);
    std::vector<int> Nums;
    std::string NumStr = "";
    while (Infile >> NumStr) {
      int Num = std::stoi(NumStr);
      Nums.push_back(Num);
    }
    return Nums;
  }

};
