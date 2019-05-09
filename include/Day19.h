#pragma once

#include "Day.h"

class Day19 : public Day {
  enum Opcode {
    ADDI,
    ADDR,
    EQRR,
    GTRR,
    MULI,
    MULR,
    SETI,
    SETR,
    INVALID
  };
  
  std::vector<int> Regs;
  struct Instr {
    Instr(Opcode opc, int op1, int op2, int op3)
        : Opc(opc), Op1(op1), Op2(op2), Op3(op3) {}
    Opcode Opc;
    int Op1, Op2, Op3;
  };
  std::vector<Instr> Instrs;
#if 0
  void parse(std::vector<std::string> Lines);
  Opcode getOpcode(std::string Inst);
  void run();
#endif
public:
  Day19() : Day(19) {
    Regs = std::vector<int>(6, 0);
  }
  void solvePart1() override;
  void solvePart2() override;
  ~Day19() override = default;
};
