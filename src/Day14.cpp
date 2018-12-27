// --- Day 14: Chocolate Charts ---

#include "Day14.h"

/// returns number of new recipes created
int Day14::fillScoreboard() {
  int Elf1Recipe = Scoreboard[Elf1];
  int Elf2Recipe = Scoreboard[Elf2];
  int NewRecipe = Elf1Recipe + Elf2Recipe;
  /// New recipe[s]
  if (NewRecipe > 9) {
    Scoreboard.push_back(1);
    Scoreboard.push_back(NewRecipe - 10);
  } else {
    Scoreboard.push_back(NewRecipe);
  }
  size_t ScoreboardSize = Scoreboard.size();
  /// New elf positions:
  Elf1 = (Elf1 + 1 + Elf1Recipe) % ScoreboardSize;
  Elf2 = (Elf2 + 1 + Elf2Recipe) % ScoreboardSize;
  return (NewRecipe > 9) ? 2 : 1;
}

void Day14::init() {
  Scoreboard = {3, 7};
  Elf1 = 0;
  Elf2 = 1;
}

void Day14::solvePart1() {
  const int Input = 990941;    // my puzzle input
//  const int Input = 2018;         // test input
  init();

  for (int i = 0; i < Input * 2; ++i) {
    fillScoreboard();
  }
  for (int i = Input; i < Input+10; ++i) {
    std::cout << Scoreboard[i];
  }
  std::cout << "\n";
}

static std::vector<int> getDigits(int Num) {
  std::vector<int> Digits;
  do {
    Digits.push_back(Num % 10);
    Num /= 10;
  } while (Num > 0);
  std::reverse(Digits.begin(), Digits.end());
  return Digits;
}


void Day14::solvePart2() {
  const int Input = 990941;
  std::vector<int> Digits = getDigits(Input);
  init();
  for (long i = 0; i < 100000000; ++i) {
    int Filled = fillScoreboard();
//    for (auto D : Scoreboard) { std::cout << D;} std::cout << "\n";
    if (Scoreboard.back() == Digits.back()) {
      bool Found = true;
      for (auto DIter = Digits.rbegin(), SIter = Scoreboard.rbegin(), DEnd = Digits.rend(); DIter != DEnd; ++DIter,++SIter) {
        if (*DIter != *SIter) {
          Found = false;
          break;
        }
      }
      if (Found) {
        std::cout << Scoreboard.size() - Digits.size() << "\n";
        return;
      }
    }
    // only check this in case fillScoreboard returned 2
    if (Filled == 2 && *std::prev(Scoreboard.end(),2) == Digits.back()) {
      bool Found = true;
      for (auto DIter = Digits.rbegin(), SIter = std::next(Scoreboard.rbegin()), DEnd = Digits.rend(); DIter != DEnd; ++DIter,++SIter) {
        if (*DIter != *SIter) {
          Found = false;
          break;
        }
      }
      if (Found) {
        std::cout << Scoreboard.size() - Digits.size() - 1 << "\n";
        return;
      }
    }
  }
  std::cout << -1 << "\n";
}

