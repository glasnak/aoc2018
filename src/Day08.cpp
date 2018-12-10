// --- Day 8: Memory Maneuver ---

#include "Day08.h"

void Day08::solvePart1() {
  //  std::vector<int> Nums = Util::getNumbers("inputs/input_08_test.txt");
  std::vector<int> Nums = Util::getNumbers("inputs/input_08.txt");
  std::deque<int> NumQueue = std::deque<int>(Nums.begin(), Nums.end());
  T.construct(NumQueue);
  std::cout << T.sum() << "\n";
}

void Day08::solvePart2() { std::cout << T.calculateValue() << "\n"; }
