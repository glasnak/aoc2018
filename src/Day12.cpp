// --- Day 12: Subterranean Sustainability ---

#include "Day12.h"

void Day12::parseInput() {
  std::vector<std::string> Lines = Util::getLines("inputs/input_12_test.txt");
  // std::vector<std::string> Lines = Util::getLines("inputs/input_12.txt");
  Lines[0].erase(0, std::string("initial state: ").size());
  for (unsigned i = 0; i < Lines[0].size(); ++i) {
    Pots.set(i, (Lines[0][i] == '#'));
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
}

static bool ruleApplies(std::bitset<5> Rule, std::deque<bool> PotQueue) {
  auto PotIter = PotQueue.begin();
  for (int j = 0; j < 5; ++j) {
    if (Rule[j] != *PotIter) {
      return false;
    }
  }
  return true;
}

// Bring on the next generation of plants, apply the \Rules to the \Pots.
void Day12::advance() {
  std::deque<bool> FivePots;
  for (int i = 0; i < 5; ++i) {
    FivePots.push_back(Pots[i]);
  }
  int PotCounter = 5;
  unsigned MaxPot = Pots.size() - 3;
  for (unsigned i = 2; i < MaxPot; ++i) {  // For each Pot, try applying each rule:
    for (auto R : Rules) {  // apply each rule
      if (ruleApplies(R.first, FivePots)) {
        Pots.set(i, R.second);
        break;
      }
      // break (finish with this pot) if already used the rule.
    }

  }
}


void Day12::solvePart1() {
  parseInput();
  int Centralization = centralizePots();

  std::cout << -1 << "\n";
}

void Day12::solvePart2() { std::cout << -1 << "\n"; }

/****

initial state: #..#.#..##......###...###

...## => #
..#.. => #
.#... => #
.#.#. => #
.#.## => #
.##.. => #
.#### => #
#.#.# => #
#.### => #
##.#. => #
##.## => #
###.. => #
###.# => #
####. => #


 */
