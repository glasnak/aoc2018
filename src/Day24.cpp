// --- Day 24: Immune System Simulator 20XX  ---

#include "Day24.h"

std::ostream &operator<<(std::ostream &OS, const Day24::Unit &U) {
  if (U.Team == Day24::ArmyTeam::ImmuneSystem) {
    OS << "Immune:    ";
  } else {
    OS << "Infection: ";
  }

  OS << U.ArmySize << " Units at " << U.HP << " HP; Attack of " << U.Attack.first
     << " dmg of type " << U.Attack.second << "; initiative = " << U.Initiative;
  if (!U.Weaknesses.empty()) {
    OS << "; weak to:";
    for (const auto &weak : U.Weaknesses) {
      OS << " [" << weak << "] ";
    }
  }
  if (!U.Immunities.empty()) {
    OS << "; immune to:";
    for (const auto &immune : U.Immunities) {
      OS << " " << immune;
    }
  }
  return OS;
}

bool Day24::isFightFinished() {
  // None are Immune or none are infection.
  return (std::none_of(Units.begin(), Units.end(), [](const Unit &U) { 
            return U.Team == ArmyTeam::ImmuneSystem; }) 
       || std::none_of(Units.begin(), Units.end(), [](const Unit &U) {
            return U.Team == ArmyTeam::Infection;
          }));
}

/// Fight Units to the death.
std::vector<Day24::Unit> Day24::fight(const int Boost) {
  
  // Not the same team and Defender isn't Immune to the Attacker's attack:
  auto canAttack = [](const Unit &Attacker, const Unit &Defender) {
    return Defender.Team != Attacker.Team
        && std::find(Defender.Immunities.begin(),
                     Defender.Immunities.end(),
                     Attacker.Attack.second) == Defender.Immunities.end();
  };
  
  /// Get an editable copy to fight with:
  auto Armies(Units);

  /// For part 2, add the specified boost to the Immune system:
  std::for_each(Armies.begin(), Armies.end(), [&Boost](Unit &U) {
    if (U.Team == Day24::ArmyTeam::ImmuneSystem)
      U.Attack.first += Boost;
  });
  
  while (!isFightFinished()) {
    std::sort(Armies.begin(), Armies.end(), std::greater<>());
    std::vector<Attack> Attacks;
    // Find all the attacks to do this round:
    for (auto &U : Armies) { // Each unit to choose their target defender:
      Unit *Target = nullptr;
      int64_t TargetMultiplier = 0;
      // Find a Target defender to attack.
      for (auto &Defender: Armies) {
        // not the same team, not immune, not.. itself?
        if (canAttack(U, Defender) &&
            std::none_of(Attacks.begin(), Attacks.end(),
                         [&](const Attack &attack) {
                           return attack.Defender == &Defender;
                         })) {
          int64_t UnitMultiplier = 1;
          if (std::find(Defender.Weaknesses.begin(),
                        Defender.Weaknesses.end(),
                        U.Attack.second)
              != Defender.Weaknesses.end()) {
            UnitMultiplier = 2;
          }
          
          if (!Target || UnitMultiplier > TargetMultiplier
              || (UnitMultiplier == TargetMultiplier
                  && Defender > *Target)) {
            Target = &Defender;
            TargetMultiplier = UnitMultiplier;
          }
        }
      }
      if (Target) {
        Attacks.emplace_back(Attack(&U, Target, TargetMultiplier));
      }
    }
    
    // sort by initiative:
    std::sort(Attacks.begin(), Attacks.end(), std::greater<>());
    

    bool Changed = false;
    for (const auto &Att: Attacks) {
      int Damage = Att.Attacker->getPower() * Att.Multiplier;
      int Killed = Damage / Att.Defender->HP;
      Att.Defender->ArmySize -= Killed;
      if (Att.Defender->ArmySize < 0)
        Att.Defender->ArmySize = 0;
      Changed = Changed || (Killed > 0);
    }

    /// Remove the dead armies:
    Armies.erase(std::remove_if(Armies.begin(), Armies.end(),
                                [](const Unit &Un) { return Un.ArmySize <= 0; }),
                 Armies.end());

    // if nothing is killed, it's over. This is a tie, sometimes caused by two 
    // opposing armies having immunities or being too weak to kill.
    if (!Changed) {
      break;
    }
  }
  return Armies;
}

void Day24::solvePart1() {
//  std::vector<std::string> Lines = Util::getLines("inputs/input_24_test.txt");
  std::vector<std::string> Lines = Util::getLines("inputs/input_24.txt");
  auto LineIt = Lines.begin();
  LineIt++; // ImmuneSystem: line
  while (!LineIt->empty()) {
    Units.emplace_back(Unit(*LineIt, ArmyTeam::ImmuneSystem));
    LineIt++;
  }
  LineIt++; // empty line
  LineIt++; // Infection: line
  while (LineIt != Lines.end()) {
    Units.emplace_back(Unit(*LineIt, ArmyTeam::Infection));
    LineIt++;
  }
  
  auto Armies = fight();
  int Sum = 0;
  for (const auto &U : Armies) {
    Sum += U.ArmySize;
  }
  std::cout << Sum << "\n";
}

void Day24::solvePart2() {
//  int Boost = 187;
  int MinBoost = 0;
  int MaxBoost = 1E6;
  while (MinBoost < MaxBoost) {
    int Boost = MinBoost + (MaxBoost - MinBoost) / 2;
    auto Armies = fight(Boost);
    // WIN, lower it:
    if (std::all_of(Armies.begin(), Armies.end(), [](const Unit& U) {
      return U.Team == ArmyTeam::ImmuneSystem;
    })) {
      MaxBoost = Boost - 1;
    } else { // Loss or tie, add more boost:
      MinBoost = Boost + 1;
    }
  }
  
  auto Armies = fight(MaxBoost);
  int Sum = 0;
  for (const auto &U : Armies) {
    Sum += U.ArmySize;
  }
  std::cout << Sum << "\n";
}


