// --- Day 24: Immune System Simulator 20XX  ---

#include "Day24.h"

std::ostream &operator<<(std::ostream &OS, const Day24::Unit &U) {
  if (U.Team == Day24::ArmyTeam::ImmuneSystem) {
    OS << "Immune:    ";
  } else {
    OS << "Infection: ";
  }

  OS << U.ArmySize << " Units at " << U.HP << " HP; Attack of " << U.Attack.first
     << " dmg of type" << U.Attack.second << "; initiative = " << U.Initiative;
  if (!U.Weaknesses.empty()) {
    OS << "; weak to:";
    for (auto &weak : U.Weaknesses) {
      OS << " " << weak;
    }
  }
  if (!U.Immunities.empty()) {
    OS << "; immune to:";
    for (auto &immune : U.Immunities) {
      OS << " " << immune;
    }
  }
  return OS;
}

/// Fight Units to the death.c
void Day24::fight() {
  
}

void Day24::solvePart1() {
  std::vector<std::string> Lines = Util::getLines("inputs/input_24_test.txt");
//  std::vector<std::string> Lines = Util::getLines("inputs/input_24.txt");
  ArmyTeam CurrentTeam = ArmyTeam::ImmuneSystem;
  for (const auto &Line : Lines) {
    if (Line.empty()) {
      CurrentTeam = ArmyTeam::Infection;
      continue;
    }
    if (Line[0] == 'I')
      continue;
    Units.emplace_back(Line, CurrentTeam);
  }
  for (const auto &U : Units) {
    std::cout << U << "\n";
  }
  std::cout << -1 << "\n";
}

void Day24::solvePart2() {
  std::cout << -1 << "\n";
}
