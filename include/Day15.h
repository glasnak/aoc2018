#pragma once

#include "Day.h"
#include "Matrix.h"
#include "Coord.h"

struct Dungeon : Matrix<char> {
  Dungeon() : Matrix() {};
  Dungeon(const unsigned int &R, const unsigned int &C) : Matrix(R, C) {};

  // Represent a creature in a Dungeon (Elf or Goblin).
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

    void attack() {}
  };
  void initialize(std::vector<std::string> Lines);

  void dump() { // kinda override, except no delimiter necessary
    Matrix::dump("");
    std::cout << Units.size() << " Units still alive...";
    // TODO more info
  }

  std::vector<Coord> getNeighbours(Coord Pos);
  void mapEnemies(char EnemyRace);
  bool Dungeon::attack(Unit U);
  void move(Unit &U);

  std::vector<Unit> Units;
  std::map<Coord, int> ElfDistances;
  std::map<Coord, int> GobDistances;
};

class Day15 : public Day {
private:
  Dungeon Cave;
  // fight methods here
  void tick();
  void fight();
public:
  Day15() : Day(15) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day15() override = default;
};
