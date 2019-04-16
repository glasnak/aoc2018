// --- Day 16: Chronal Classification ---

#include "Day16.h"

/// parse this:
// Before: [3, 2, 1, 1]
// 9 2 1 2
// After:  [3, 2, 2, 1]
void Day16::parse(std::vector<std::string> Lines) {
  auto LinesSize = Lines.size();
  for (unsigned i = 0; i < LinesSize; ++i) {
    Execution exec;
    if (Lines[i][0] != 'B')
      continue;
    exec.Before = {0, 0, 0, 0};
    sscanf(Lines[i].c_str(),
           "Before: [%d, %d, %d, %d]",
           &exec.Before[0],
           &exec.Before[1],
           &exec.Before[2],
           &exec.Before[3]);
    ++i;
    exec.Instr = {0, 0, 0, 0};
    sscanf(Lines[i].c_str(),
           "%d %d %d %d",
           &exec.Instr[0],
           &exec.Instr[1],
           &exec.Instr[2],
           &exec.Instr[3]);
    ++i;
    exec.After = {0, 0, 0, 0};
    sscanf(Lines[i].c_str(),
           "After: [%d, %d, %d, %d]",
           &exec.After[0],
           &exec.After[1],
           &exec.After[2],
           &exec.After[3]);
    Examples.emplace_back(exec);
  }
}

void Day16::solvePart2() {
//  std::vector<std::string> Lines = Util::getLines("inputs/input_16.txt");
  std::cout << -1 << "\n";
}

