// --- Day 12: Subterranean Sustainability ---

#include "Day12.h"

const int OFFSET = 5;

void Day12::parseInput() {
  Pots.reset();
  Rules.clear();
//  std::vector<std::string> Lines = Util::getLines("inputs/input_12_test.txt");
   std::vector<std::string> Lines = Util::getLines("inputs/input_12.txt");
  Lines[0].erase(0, std::string("initial state: ").size());
  for (size_t i = 0; i < Lines[0].size(); ++i) {
    Pots.set(i + OFFSET, (Lines[0][i] == '#'));
  }
  for (size_t i = 2; i < Lines.size(); ++i) {
    std::bitset<5> Condition;
    // 0123456789
    // .#.#. => #
    for (unsigned j = 0; j < 5; ++j) {
      Condition.set(j, Lines[i][j] == '#');
    }
    Rules[Condition] = (Lines[i][9] == '#');
  }
}

// Bring on the next generation of plants, apply the \Rules to the \Pots.
void Day12::advance() {
  auto NewPots = Pots;
  unsigned MaxPot = Pots.size() - 3;
  for (unsigned i = 2; i < MaxPot; ++i) {
    std::bitset<5> PotQuintet;
    for (unsigned j = 0; j < 5; ++j) {
      PotQuintet.set(j, Pots[i - 2 + j]);
    }
    if (Rules.count(PotQuintet)) {
      NewPots.set(i, Rules[PotQuintet]);
    } else {
      NewPots.set(i, false);
    }
  }
  Pots = NewPots;
}


void Day12::printGeneration() {
  for (int i = 0, e = Pots.size(); i < e; ++i) {
    std::cout << ((Pots[i]) ? '#' : '.');
  }
  std::cout << "\n";
}

long Day12::sumPlants(long Centralization) {
  long Sum = 0;
  for (size_t i = 0; i < Pots.size(); ++i) {
    Sum += Pots[i] * (i - OFFSET - Centralization);
  }
  return Sum;
}

// normalize the bitset. Five zeroes on each side, in a way, make it infinite.
// Every couple of generations (FIXME: optimize this?),
// run the pot centralization algorithm to shift bitset to the centre.
// returns by the number of pots we needed to centralize.
int Day12::centralizePots() {
  int MinPot = 0;
  int MaxPot = NUM_POTS - 1;
  while (!Pots[MinPot]) MinPot++;
  while (!Pots[MaxPot]) MaxPot--;
  assert(MaxPot < NUM_POTS - 2 && MinPot > 2);
  // shift to the position of .....#[all pots]#.....
  auto NewPots = Pots;
  NewPots.reset();
  unsigned Edge = 10;
  for (unsigned i = 0; i < Edge; ++i) {
    NewPots.set(i, false);
  }
  unsigned Idx = Edge;
  for (int j = MinPot; j <= MaxPot+1; ++j, ++Idx) {
    NewPots.set(Idx, Pots[j]);
  }

  Pots = NewPots;
  return Edge - MinPot;
}

void Day12::solvePart1() {
  parseInput();
  for (unsigned i = 0; i < 20; ++i) {
    advance();
  }
  std::cout << sumPlants() << "\n";
}


void Day12::solvePart2() {
  unsigned long DesiredAnswer = 50000000000;
  parseInput();
  long Centralization = 0;
  unsigned long Extrapolation = 1000000000;
  unsigned long Iteration = DesiredAnswer / Extrapolation;
  // Far enough, patterns emerge. All we need to do is extrapolate.
  std::vector<long> Sums;
  for (int i = 0; i < 4; ++i) {
    Centralization += centralizePots();
    for (unsigned j = 0; j < Iteration; ++j) {
      advance();
    }
    Sums.push_back(sumPlants(Centralization));
  }
  // assume the sums grow linearly, i.e. diff is always the same:
  assert(Sums.back() - *std::prev(Sums.end(), 2) ==
         *std::prev(Sums.end(), 2) - *std::prev(Sums.end(), 3));
  long SumDiff = Sums.back() - *std::prev(Sums.end(), 2);

  std::cout << (Extrapolation * SumDiff) << "\n";
}
