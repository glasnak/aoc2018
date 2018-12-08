// --- Day 5: Alchemical Reduction ---

#include "Day05.h"

// [a-z]+[A-Z], in any order
static bool react(char A, char B) { return (A == B + 32 || A == B - 32); }

std::deque<char> Day05::reactPolymer(std::deque<char> PolymerQ) {
  std::deque<char> NewPolymerQ;
  NewPolymerQ.clear();
  char Popper;
  while (!PolymerQ.empty()) {
    Popper = PolymerQ.front();
    NewPolymerQ.emplace_back(Popper);
    PolymerQ.pop_front();
    while (!NewPolymerQ.empty() && !PolymerQ.empty() &&
           react(NewPolymerQ.back(), PolymerQ.front())) {
      NewPolymerQ.pop_back();
      PolymerQ.pop_front();
    }
  }
  return NewPolymerQ;
}

void Day05::solvePart1() {
  Polymer = Util::getCharDeque("inputs/input_05.txt");
  //  Polymer = Util::getCharDeque("inputs/input_05_test.txt");
  std::cout << reactPolymer(Polymer).size() << "\n";
}

void Day05::solvePart2() {
  assert(!Polymer.empty());
  std::deque<char> ReducedPolymer;
  size_t Shortest = std::numeric_limits<int>::max();
  for (char c = 'a', C = 'A'; c <= 'z'; ++c, ++C) {
    ReducedPolymer.clear();
    std::copy_if(Polymer.begin(), Polymer.end(),
                 std::back_inserter(ReducedPolymer),
                 [c, C](unsigned char x) { return x != c && x != C; });
    size_t NewPolySize = reactPolymer(ReducedPolymer).size();
    if (Shortest > NewPolySize)
      Shortest = NewPolySize;
  }
  std::cout << Shortest << "\n";
}
