// --- Day 12: Subterranean Sustainability ---

#include "Day12.h"

const int OFFSET = 100; // todo remove this.

void Day12::parseInput() {
//  std::vector<std::string> Lines = Util::getLines("inputs/input_12_test.txt");
   std::vector<std::string> Lines = Util::getLines("inputs/input_12.txt");
  Lines[0].erase(0, std::string("initial state: ").size());
  for (unsigned i = 0; i < Lines[0].size(); ++i) {
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

static bool ruleApplies(std::bitset<5> Rule, std::deque<bool> PotQueue) {
  auto PotIter = PotQueue.begin();
  for (int j = 0; j < 5; ++j, ++PotIter) {
    if (Rule[j] != *PotIter) {
      return false;
    }
  }
  //  std::cout << "Applied: ";
  //    for (auto Item : PotQueue) {
  //      std::cout << Item;
  //    }
  //    std::cout << " === " << Rule.to_string() << "\n";
  return true;
}

// Bring on the next generation of plants, apply the \Rules to the \Pots.
void Day12::advance() {
  std::deque<bool> FivePots;
  for (int i = 0; i < 5; ++i) {
    FivePots.push_back(Pots[i]);
  }
  unsigned MaxPot = Pots.size() - 3;
  for (unsigned i = 2; i < MaxPot; ++i) { // A rule for every Pot
    // std::cout << "going through " << Rules.size() << " rules!\n";
    bool Applied = false;
    for (auto R : Rules) { // Pick the rule
      /// FIXME: i can just... create new bitset and use that as a key, can't I?
      // that's bound to speed things up.
      if (ruleApplies(R.first, FivePots)) {
        Pots.set(i, R.second);
        Applied = true;
        break;
      }
      // break (finish with this pot) if already used the rule.
    }
    if (!Applied) {
      // std::cout << "couldn't find the rule\n";
      Pots.set(i, false);
    }
    FivePots.pop_front();
    // at start, we have 0..4, i starts with 2, so we need to add 2+3
    FivePots.push_back(Pots[i + 3]);
  }
}

void Day12::printGeneration() {
  for (int i = 0, e = Pots.size(); i < e; ++i) {
    std::cout << ((Pots[i]) ? '#' : '.');
  }
  std::cout << "\n";
}

long Day12::sumPlants() {
  // all of those minus OFFSET
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
  // printGeneration();
  for (auto i = 0; i < 20; ++i) {
    advance();
    // printGeneration();
  }

  std::cout << sumPlants() << "\n";
}

void Day12::solvePart2() {
  int Centralization = centralizePots();
  std::cout << -1 << "\n";
}
