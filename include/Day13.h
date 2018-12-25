#pragma once

#include "Day.h"
#include "Matrix.h"
#include "Coord.h"

struct RailroadGrid : Matrix<char> {
  
  struct MineCart {
    explicit MineCart(int ID, Coord Position, Direction Facing,
                      int IntersectionDecision = 3)
        : ID(ID), Position(Position), Facing(Facing),
          IntersectionDecision(IntersectionDecision) {}

    int ID;
    Coord Position;
    Direction Facing;  // S(1,0), N(-1,0), E(0,1), W(0,-1)
    int IntersectionDecision;
    // for std::sort;
    bool operator<(const MineCart &rhs) const {
      if (Position.y < rhs.Position.y)
        return true;
      else if (Position.y > rhs.Position.y)
        return false;
      else
        return Position.x < rhs.Position.x;
    }
    bool operator==(const MineCart &rhs) const {
      return ID == rhs.ID;
    }
    bool operator!=(const MineCart &rhs) const {
      return !(rhs == *this);
    }
  };
  std::vector<MineCart> MineCarts;
  
  RailroadGrid() : Matrix() {};
  RailroadGrid(const unsigned int &R, const unsigned int &C)  : Matrix(R, C) {};

  void initialize(std::vector<std::string> Lines);
  void clearGrid();
  void advanceCart(MineCart &MC);
  bool tick(bool QuitOnCollision=true);
  bool hasCollision(MineCart MC);

  /// Mostly a copy of Matrix::dump() except it prints Minecarts as well.
  void dumpWithMineCarts() const {
    std::cout << "RailGrid of size " << Rows << "x" << Columns << ":\n";
    if (M.empty()) {
      std::cout << "RailGrid empty.\n";
      return;
    }
    for (unsigned i = 0; i < Rows; ++i) {
      for (unsigned j = 0; j < Columns; ++j) {
        bool Printed = false;
        for (auto MC : MineCarts) {
          if (Coord(i,j) == MC.Position) {
            switch(MC.Facing) {
            case Direction::NORTH: std::cout << "^"; break;
            case Direction::EAST:  std::cout << ">"; break;
            case Direction::SOUTH: std::cout << "v"; break;
            case Direction::WEST:  std::cout << "<"; break;
            }
            Printed = true;
          }
        }
        if (!Printed)
          std::cout << M[i][j];
      }
      std::cout << "\n";
    }
  }
};


class Day13 : public Day {
private:
  void parseInput();

  RailroadGrid Grid;
public:
  Day13() : Day(13) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day13() override = default;
};




