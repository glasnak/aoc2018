// --- Day 2: Inventory Management System ---

#include "Day02.h"

void Day02::solvePart1() {
  Strings.clear();
  Strings = Util::getLines("inputs/input_02.txt");
  int Twos = 0;
  int Threes = 0;
  for (const auto &Str : Strings) {
    // py: collections.Counter
    std::map<char, int> LineCounter;
    for (char Ch : Str)
      LineCounter[Ch]++;

    bool Two = false;
    bool Three = false;
    for (const auto &Count : LineCounter) {
      if (Count.second == 2)
        Two = true;
      else if (Count.second == 3)
        Three = true;
      // speedy exit (makes little difference due to short strings)
      if (Two && Three)
        break;
    }
    // "+= false" does nothing
    Twos += Two;
    Threes += Three;
    LineCounter.clear();
  }
  std::cout << Twos * Threes << "\n";
}

void Day02::solvePart2() {
  unsigned long Len = Strings.size();
  for (unsigned long i = 0; i < Len; ++i) {
    for (unsigned long j = i + 1; j < Len; ++j) {
      if (areNeighbours(Strings[i], Strings[j])) {
        printCommon(Strings[i], Strings[j]);
      }
    }
  }
}


// Are the strings different in only a single character?
// Luckily we don't need to reimplement entire Levenshtein Distance... yet.
bool Day02::areNeighbours(const std::string One, const std::string Two) {
  bool SawDiff = false;
  for (unsigned long i = 0; i < LineLength; ++i) {
    if (One[i] != Two[i]) {
      if (SawDiff)
        return false;
      else
        SawDiff = true;
    }
  }
  return true;
}

// FIXME: inefficient. Copy the two parts before and after differing char
// instead.
void Day02::printCommon(const std::string One, const std::string Two) {
  std::string Str;
  for (auto It1 = begin(One), It2 = begin(Two); It1 != end(One); ++It1, ++It2) {
    if (*It1 == *It2)
      Str += *It1;
  }
  std::cout << Str << "\n";
}
