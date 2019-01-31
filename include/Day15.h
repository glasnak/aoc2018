#pragma once

#include "Day.h"
#include "Matrix.h"
#include "Coord.h"

struct Dungeon : Matrix<char> {
  Dungeon() : Matrix() {};
  Dungeon(const unsigned int &R, const unsigned int &C, int ElfPower = 3) : Matrix(R, C), ElfPower(ElfPower) {};

  // Represent a creature in a Dungeon (Elf or Goblin).
  int ElfPower;
  struct Unit {
    Unit(char R, Coord Pos) : Race(R), Position(Pos), Health(200) {};
    // can Attack or Move.
    char Race;  // G for Goblin, E for Elf.
    Coord Position;
    int Health;
    // for std::sort;
    bool operator<(const Unit &rhs) const { // Note reversed x,y
      // FIXME: use Coord::operator< instead.
      if (Position.x < rhs.Position.x)
        return true;
      else if (Position.x > rhs.Position.x)
        return false;
      else
        return Position.y < rhs.Position.y;
    }
    bool operator==(const Unit &rhs) const {
      return Position == rhs.Position && Race == rhs.Race && Health == rhs.Health;
    }
    bool operator!=(const Unit &rhs) const {
      return !(rhs == *this);
    }
  };
  void initialize(std::vector<std::string> Lines);

  void dump() { // kinda override, except no delimiter necessary
    Matrix::dump("");
    std::cout << Units.size() << " Units still alive:\n";
    for (const auto &U : Units) {
      std::cout << "    " << U.Race << " [" << U.Health << "]\n";
    }
  }

  std::vector<Coord> getNeighbours(Coord Pos);
  void mapEnemies(char EnemyRace);
  bool attack(Unit U, bool &GameOver);
  void move(Unit &U);

  bool checkWinner() {
    bool ElfAlive = false; 
    bool GobAlive = false;
    for (const auto &U : Units) {
      if (U.Health <= 0) continue;
      if (U.Race == 'E')
        ElfAlive = true;
      else
        GobAlive = true;
    }
    if (!ElfAlive || !GobAlive) {
//      char Winner = (!ElfAlive) ? 'G' : 'E'; 
//      std::cout << "Winner: " << Winner << ".\n";
      return true;
    }
    return false;
  }

  Unit *getUnit(Coord C) {
    for (auto &U : Units) {
      if (U.Position == C)
        return &U;
    }
    return nullptr;
  }
  
  int sumHP() {
    int ElfHP = 0;
    int GobHP = 0;
    for (const auto &U : Units) {
      if (U.Health <= 0) continue;
      if (U.Race == 'E')
        ElfHP += U.Health;
      else
        GobHP += U.Health;
    }
    return (ElfHP) ? ElfHP : GobHP;
  }
  
  std::vector<Unit> Units;
  // TODO: Need a map<Position, Units> instead of Unit.Position to better work with it...
  std::map<Coord, int> ElfDistances;
  std::map<Coord, int> GobDistances;
};

class Day15 : public Day {
private:
  Dungeon Cave;
  // fight methods here
  bool tick();
  void fight();
public:
  Day15() : Day(15) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day15() override = default;
};
