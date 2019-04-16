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

void Day16::solvePart1() {
  std::vector<std::string> Lines = Util::getLines("inputs/input_16.txt");
  parse(Lines);
  int ThreeOrMore = 0;
  for (const auto &E : Examples) {
    std::vector<bool> PossibleOpcodes(16, false);
    int Expected = E.After[E.Instr[3]];
    int Ra = E.Before[E.Instr[1]];
    int Rb = E.Before[E.Instr[2]];
    int Ia = E.Instr[1];
    int Ib = E.Instr[2];
    
    PossibleOpcodes[0] = (Expected == (Ra + Rb));      // 6
    PossibleOpcodes[1] = (Expected == (Ra + Ib));      // 9
    PossibleOpcodes[2] = (Expected == (Ra * Rb));      // 14
    PossibleOpcodes[3] = (Expected == (Ra * Ib));      // 1
    PossibleOpcodes[4] = (Expected == (Ra & Rb));      // 2
    PossibleOpcodes[5] = (Expected == (Ra & Ib));      // 3
    PossibleOpcodes[6] = (Expected == (Ra | Rb));      // 12
    PossibleOpcodes[7] = (Expected == (Ra | Ib));      // 0
    PossibleOpcodes[8] = (Expected == (Ra));           // 5
    PossibleOpcodes[9] = (Expected == (Ia));           // 8
    PossibleOpcodes[10] = (Expected == (Ia > Rb));     // 4
    PossibleOpcodes[11] = (Expected == (Ra > Ib));     // 15
    PossibleOpcodes[12] = (Expected == (Ra > Rb));     // 13
    PossibleOpcodes[13] = (Expected == (Ia == Rb));    // 7
    PossibleOpcodes[14] = (Expected == (Ra == Ib));    // 11
    PossibleOpcodes[15] = (Expected == (Ra == Rb));    // 10
    auto Count = std::count(PossibleOpcodes.begin(), PossibleOpcodes.end(), true);
    ThreeOrMore += (Count >= 3);
  }
  std::cout << /*"Over 3: " <<*/ ThreeOrMore << "\n";
}

