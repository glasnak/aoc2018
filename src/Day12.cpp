// --- Day 12: Subterranean Sustainability ---

#include "Day12.h"

const int OFFSET = 100; // todo remove this.

void Day12::parseInput() {
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

long Day12::sumPlants() {
  long Sum = 0;
  for (size_t i = 0; i < Pots.size(); ++i) {
    Sum += Pots[i] * (i-OFFSET);
  }
  return Sum;
}

// normalize the bitset. Five zeroes on each side, in a way, make it infinite.
// Every couple of generations (FIXME: optimize this?),
// run the pot centralization algorithm to shift bitset to the centre.
// returns by the number of pots we needed to centralize.
int Day12::centralizePots() {
  unsigned MinPot = 0;
  unsigned NumPots = Pots.size();
  unsigned MaxPot = NumPots - 1;
  while (!Pots[MinPot])
    MinPot++;
  while (!Pots[MaxPot])
    MaxPot--;
  // TODO: normalize Pots, move it to the "centre"
  return 0;
}

void Day12::solvePart1() {
  parseInput();
//  printGeneration();
  for (int i = 0; i < 20; ++i) {
    advance();
//    printGeneration();
  }

  std::cout << sumPlants() << "\n";
}

void Day12::solvePart2() {
  //  parseInput(); // set it all up again
  //  int Centralization = centralizePots();
  std::cout << -1 << "\n";
}
