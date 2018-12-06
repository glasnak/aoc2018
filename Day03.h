#pragma once

#include "Day.h"
// #include <boost/algorithm/string.hpp>

class Day03 : public Day {
private:
  std::vector<std::string> Strings;
  struct Coord {
    int x;
    int y;

    Coord() : x(0), y(0) {}
    Coord(const int &X, const int &Y) : x(X), y(Y) {}

    // necessary for unordered_set comparison
    bool operator==(const Coord &other) const {
      return (x == other.x && y == other.y);
    }

    // needed for unordered_set hashing
    size_t operator()(const Coord &ToHash) const noexcept {
      size_t hash = static_cast<unsigned>(ToHash.x + 137 * ToHash.y);
      return hash;
    }

    void dump() const { std::cout << "[" << x << "," << y << "]\n"; }
  };
  std::unordered_set<Coord, /* hash= */ Coord> Overlappers;

  struct Area {
    explicit Area(const std::string &Input) {
      std::vector<std::string> InputNums;

      // #4 @ 5,5: 2x2
      int Posx, Posy, Sizex, Sizey, id;
      sscanf(Input.c_str(), "#%d @ %d,%d: %dx%d", &id, &Posx, &Posy, &Sizex,
             &Sizey);
      ID = id;
      Pos = Coord{Posx, Posy};
      Size = Coord{Sizex, Sizey};
      // FIXME? boost would even do error-checking
      // boost::split(InputNums, Input, boost::is_any_of("#@,:x"));
      // ID = stoi(InputNums[1]);
      // Pos = Coord{stoi(InputNums[2]), stoi(InputNums[3])};
      // Size = Coord{stoi(InputNums[4]), stoi(InputNums[5])};
    }
    int ID;
    Coord Pos;  // distance from [0,0]
    Coord Size; // width, height
    bool Overlaps = false;
    void dump() {
      std::cout << " Area #" << ID << "\n";
      std::cout << " Pos: " << Pos.x << "," << Pos.y << "\n";
      std::cout << " Size: " << Size.x << "x" << Size.y << "\n";
    }
  };
  std::vector<Area> Areas;
  bool areasOverlap(Area &A, Area &B);
  void addOverlappers(Coord TopLeft, Coord BottomRight);

public:
  Day03() : Day(3) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day03() override = default;
};
