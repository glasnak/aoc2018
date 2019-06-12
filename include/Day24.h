#pragma once

#include "Day.h"
#include <boost/algorithm/string.hpp>


class Day24 : public Day {

  enum ArmyTeam {
    ImmuneSystem,
    Infection,
    None
  };

  struct Unit {
    int ArmySize;
    int HP;
    std::pair<int, std::string> Attack;
    int Initiative;
    std::vector<std::string> Immunities, Weaknesses;
    ArmyTeam Team;

    static std::vector<std::string> parseWeakImmune(const std::vector<std::string> &Elements,
                                                    const std::string &WeakOrImmune) {
      std::vector<std::string> Result;
      Result.clear();
      auto Element = std::find(Elements.begin(), Elements.end(), WeakOrImmune);
      if (Element != Elements.end()) {
        std::advance(Element, 2);
        while (Element->back() == ',') {
          Result.emplace_back(Element->substr(0, Element->size() - 1));
          ++Element;
        }
        Result.emplace_back(*Element);
      }
      return Result;
    }


    Unit(const std::string &Line, const ArmyTeam AT) : Team(AT) {
      std::vector<std::string> Elements;
      boost::split(Elements, Line, boost::is_any_of(" ();"));
      ArmySize = std::stoi(Elements.at(0));
      HP = std::stoi(Elements.at(4));

      auto Element = std::find(Elements.begin(), Elements.end(), "does");
      ++Element;
      auto AttackStrength = std::stoi(*Element);
      ++Element;
      Attack = std::make_pair(AttackStrength, *Element);
      Element = std::find(Elements.begin(), Elements.end(), "initiative");
      ++Element;
      Initiative = std::stoi(*Element);
      Immunities.clear(); 
      Weaknesses.clear();
      Weaknesses = parseWeakImmune(Elements, "weak");
      Immunities = parseWeakImmune(Elements, "immune");
    }

    int getPower() const { return ArmySize * Attack.first; }

    bool operator<(const Unit &Other) const {
      if (getPower() < Other.getPower())
        return true;
      return (getPower() == Other.getPower() ? (Initiative < Other.Initiative) 
                                               : false);
    }
    bool operator>(const Unit &Other) const { return Other < *this; }
  };
  
  struct Attack {
    Attack(Unit *Att, Unit *Def, int Multi)
        : Attacker(Att), Defender(Def), Multiplier(Multi) {}
    Unit *Attacker;
    Unit *Defender;
    int Multiplier;
    bool operator<(const Attack &Other) const {
      return Attacker->Initiative < Other.Attacker->Initiative;
    }
    bool operator>(const Attack &Other) const {
      return Other < *this;
    }
  };

  std::vector<Unit> Units;

  bool isFightFinished();
  std::vector<Day24::Unit> fight(int Boost = 0); 
  
public:
  friend std::ostream &operator<<(std::ostream &OS, const Unit &U);
  Day24() : Day(24) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day24() override = default;
};
