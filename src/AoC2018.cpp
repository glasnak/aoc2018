// Advent of Code 2018, this time in C++
// @author glasnak

#include <cassert>
#include <iostream>
#include <string>

#include "DayList.h"

template <typename T> Day *instantiator() { return new T; }

typedef Day *(*instantiator_ptr)();
const instantiator_ptr Classes[] = {
    nullptr,
    &instantiator<Day01>,
    &instantiator<Day02>,
    &instantiator<Day03>,
    &instantiator<Day04>,
    &instantiator<Day05>,
    &instantiator<Day06>,
    &instantiator<Day07>,
    &instantiator<Day08>,
    &instantiator<Day09>,
//    &instantiator<Day10>,
};

// Run all the tests of the AoC
// params
int main(int argc, char const *argv[]) {
  if (argc > 2) {
    std::cerr << "Usage: ./aoc2018 [n] where n is the day to solve.\n";
    return 1;
  }
  // TODO error-checking
  int DayNum = (argc == 2) ? std::stoi(argv[1]) : 0;
  if (DayNum < 0 || DayNum > 25) {
    std::cerr << "Please specify a correct day (0 for solving all days).\n";
    return 1;
  }
  if (DayNum) {
    Day *D = Classes[DayNum]();
    D->prettySolve();
  } else {
    std::cout << "Solving all days:\n";
    int NumDays = sizeof(Classes) / sizeof(void *);
    for (auto i = 1; i < NumDays; ++i) {
      Day *D = Classes[i]();
      D->prettySolve();
    }
  }

  return 0;
}
