// --- Day 19: Settlers of The North Pole ---

#include "Day19.h"

static const bool TESTING = false;


/// Create grid out of input.
void Day19::parse(const std::vector<std::string> &Lines) {
}


void Day19::solvePart1() {
  std::string InputFile = TESTING ? "inputs/input_19_test.txt" : "inputs/input_19.txt";
  std::vector<std::string> Lines = Util::getLines(InputFile);
  parse(Lines);

  std::cout << -1 << "\n";
}

void Day19::solvePart2() {
  std::cout << -1 << "\n";
}