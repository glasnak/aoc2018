#pragma once

#include "Day.h"

class Day16 : public Day {
private:
  struct Execution {
    std::vector<int> Before; // Regs 0..3 before execution
    std::vector<int> After;  // Regs 0..3 after execution
    std::vector<int> Instr;  // Opc, A, B, C
    void dump() {
      std::cout << "==================\n";
      std::cout << "Before: ";
      for (auto B : Before) {std::cout << B << ", ";}
      std::cout << "\n";
      for (auto I : Instr) {std::cout << I << " ";}
      std::cout << "\nAfter: ";
      for (auto A : After) {std::cout << A << ", ";}
      std::cout << "\n";
      std::cout << "==================\n";
    }
  };
  
  std::vector<Execution> Examples;
  void parse(std::vector<std::string> Lines);
  
public:
  Day16() : Day(16) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day16() override = default;
};
