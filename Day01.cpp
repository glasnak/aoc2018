// --- Day 1: Chronal Calibration ---
// Part one actually solved with awk:
//   awk '{ sum+=$1} END {print sum}' input_01.txt
//

#include "Day01.h"

void Day01::solvePart1() {
  Nums.clear();
  Nums = Util::getNumbers("inputs/input_01.txt");
  assert(!Nums.empty() && "Can't read input!");
  int Acc = std::accumulate(Nums.begin(), Nums.end(), 0);
  std::cout << Acc << "\n";
}

void Day01::solvePart2() {
  if (Nums.empty())
    Nums = Util::getNumbers("inputs/input_01.txt");
  std::unordered_set<int> Sums;
  int Sum = 0;
  unsigned NumSums = 1;
  Sums.insert(0);
  while (true) {
    for (int N : Nums) {
      Sum += N;
      Sums.emplace(Sum);
      if (++NumSums != Sums.size()) {
        std::cout << Sum << "\n";
        return;
      }
    }
  }
}
