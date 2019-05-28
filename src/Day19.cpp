// --- Day 19: Go With The Flow ---

#include "Day19.h"


#if 0
static const bool TESTING = false;

/// parse the program
// #ip 3
// seti 5 0 1
// addi 0 1 0
// ...
void Day19::parse(std::vector<std::string> Lines) {
  sscanf(Lines[0].c_str(), "#ip = %d", &IP);
  int NumLines = Lines.size();
  char Inst[4]; // = {' ',' ',' ',' '};  /// is this init even necessary
  int d1, d2, d3;
  Instrs.clear();
  for (int i = 1; i < NumLines; ++i) {
    sscanf(Lines[i].c_str(), "%c%c%c%c %d %d %d", 
        &Inst[0], &Inst[1], &Inst[2], &Inst[3], &d1, &d2, &d3);
    Instrs.emplace_back(Instr(getOpcode(Inst), d1, d2, d3));  
  }
  
  for (auto I : Instrs) {
    std::cout << "IP = " << IP << "; Instr: [" << I.Opc << "] " << I.Op1 << " " << I.Op2 << " " << I.Op3 << "\n";
  }
}

// "seti" -> Opcode::SETI
Day19::Opcode Day19::getOpcode(std::string Inst) {
  std::cout << "Instr  ==  " << Inst << "\n";
  switch (Inst[0]) { /// [0]:aegms x [3]:ri
  case 'a':
    return (Inst[3] == 'i') ? Day19::Opcode::ADDI : Day19::Opcode::ADDR;
  case 'e':
    return Day19::Opcode::EQRR;
  case 'g':
    return Day19::Opcode::GTRR;
  case 'm':
    return (Inst[3] == 'i') ? Day19::Opcode::MULI : Day19::Opcode::MULR;
  case 's':
    return (Inst[3] == 'i') ? Day19::Opcode::SETI : Day19::Opcode::SETR;
  default:
    return Day19::Opcode::INVALID_TYPE;
  }
}

/// run the program
// example program:
//       #ip 0 
//       ip=0 [0, 0, 0, 0, 0, 0]   seti 5 0 1   [0, 5, 0, 0, 0, 0]
//       ip=1 [1, 5, 0, 0, 0, 0]   seti 6 0 2   [1, 5, 6, 0, 0, 0]
//       ip=2 [2, 5, 6, 0, 0, 0]   addi 0 1 0   [3, 5, 6, 0, 0, 0]
//       ip=4 [4, 5, 6, 0, 0, 0]   setr 1 0 0   [5, 5, 6, 0, 0, 0]
//       ip=6 [6, 5, 6, 0, 0, 0]   seti 9 0 5   [6, 5, 6, 0, 0, 9]
//
// Note that from Day 16, add/mul works like this:
//     Addition:
// (addr A B C) == xC = xA+xB;
// addr (add register) stores into register C the result of adding register A and register B.
// addi (add immediate) stores into register C the result of adding register A and value B.
//
//     Multiplication:
// mulr (multiply register) stores into register C the result of multiplying register A and register B.
// muli (multiply immediate) stores into register C the result of multiplying register A and value B.

void Day19::run() {
  int IPReg = IP;
  // First line sets the IP:
  int NumInstrs = Instrs.size();
  for (long long int i = 0; true; ++i) {
    IP = Regs[IPReg];
    auto I = Instrs[IP];
    if (IP >= NumInstrs || IP < 0) {
      std::cout << "HALT at #" << i << ".\n";
      for (const auto &R : Regs) { std::cout << R << ", "; }
      std::cout << "\n---------------\n";
      break;
    }
//    std::cout << "\nBefore: ";
//    for (const auto &R : Regs) { std::cout << R << ", "; }
//    std::cout << "\nIP = " << IP << "; executing [" << I.Opc << "] " << I.Op1 << " " << I.Op2 << " " << I.Op3 << "\n";
    switch (I.Opc) {
    case ADDI:  // xC = xA + B;
      Regs[I.Op3] = Regs[I.Op1] + I.Op2;
      break;
    case ADDR:  // xC = xA + xB;
      Regs[I.Op3] = Regs[I.Op2] + Regs[I.Op1];
      break;
    case EQRR:  // Regs[C] = Ra == Rb;
      Regs[I.Op3] = (Regs[I.Op1] == Regs[I.Op2]);
      break;
    case GTRR:  // Regs[C] = Ra >  Rb;
      Regs[I.Op3] = (Regs[I.Op1] > Regs[I.Op2]);
      break;
    case MULI:
      Regs[I.Op3] = Regs[I.Op1] * I.Op2;
      break;
    case MULR:
      Regs[I.Op3] = Regs[I.Op1] * Regs[I.Op2];
      break;
    case SETI:
      Regs[I.Op3] = I.Op1;
//      Regs[I.Op2] = Regs[IPReg];
      break;
    case SETR:
      Regs[I.Op3] = Regs[I.Op1];
//      Regs[I.Op2] = Regs[IPReg];
      break;
    case INVALID_TYPE:
      assert(!"Invalid opcode"); break;
    }
//    std::cout << "After: ";
//    for (const auto &R : Regs) { std::cout << R << ", "; }
//    std::cout << "\n---------------\n";
    Regs[IPReg]++;
  }
}
#endif


/// A disassembled input program, with very minor optimizations.
/// Takes a single argument and finds sum of all its factors (including 1 and itself).
static int runDisassembled(const int x4) {
  int x0 = 0;
  for (int x2 = 1; x2 <= x4; ++x2) {
    for (int x5 = 1; x5 <= x4; ++x5) {
      int x2x5 = x2 * x5;
      if (x4 == x2x5 ) {
        x0 += x2;
      } else if (x4 < x2x5)
        break;
    }
  }
  return x0;
}


void Day19::solvePart1() {
  /// None of this matters. Needs to be manually disassembled and ran that way, 
  /// otherwise it will halt in a few years at best.
//  std::string InputFile = TESTING ? "inputs/input_19_test.txt" : "inputs/input_19.txt";
//  std::vector<std::string> Lines = Util::getLines(InputFile);
//  parse(Lines);
//  run();
  std::cout << runDisassembled(926) << "\n";
}

void Day19::solvePart2() {
  std::cout << runDisassembled(10551326) << "\n";
}

