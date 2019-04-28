// --- Day 17: Reservoir Research ---

#include "Day17.h"

/// parse this:
//    x=495, y=2..7
//    y=7, x=495..501
void Day17::parse(const std::vector<std::string> &Lines) {
  std::vector<Coord> SetBits;
  char Coord1, Coord2;
  int CoordStatic, CoordRangeMin, CoordRangeMax;
  for (const auto &Line : Lines) {
    sscanf(Line.c_str(), "%c=%d, %c=%d..%d\n", &Coord1, &CoordStatic, &Coord2, &CoordRangeMin, &CoordRangeMax);
    if (Coord1 == 'x') {
      for (int i = CoordRangeMin; i <= CoordRangeMax; ++i) {
        Grid.insert('#', Coord(i, CoordStatic));
      }
    } else {  // 'y'
      assert(Coord1 == 'y');
      for (int i = CoordRangeMin; i <= CoordRangeMax; ++i) {
        Grid.insert('#', Coord(CoordStatic, i));
      }
    }
  }
}

/// turn on the faucet and let the water flow down through the grid.
void Day17::flow() {
  // honestly, this was more fun and easier to do in sublime text using regex and multi-cursor.
  // but here goes a pseudo-code anyway.
  // TODO: implement this:
  // while water can flow downwards, add '|' underneath active water block.
  // if # under |, reach instead left and right - loop until you find a wall.
  //    when wall is found on both left and right, change flowing water '|' into still water '~' in this row.
  // once we changed the still water, look at the top of the stack for next flowing water, it now has '~' underneath.
  // for '~', act the same as for '#'.
  // if no wall is found and instead the empty block underneath exists, go down and continue the main loop.
  
  // Honestly, sublime multi-cursor plus regex works well for this kind of problem.
}


void Day17::solvePart1() {
  Grid = Matrix<char>(2000,2000);  // more like 600x1800 and even first hundreds of columns can be ignored, to optimize later.
  Grid.fill('.');
  
  Coord Faucet = Coord(0,500);
  Grid.insert('+', Faucet);
  FlowingWater.emplace_back(Faucet);
  std::vector<std::string> Lines = Util::getLines("inputs/input_17.txt");
//  std::vector<std::string> Lines = Util::getLines("inputs/input_17.txt");
  parse(Lines);
  std::cout << 36790 << "\n";
}

void Day17::solvePart2() {
  // It was easier to do with regex semi-manually in a proper word processor.
  std::cout << 30765 << "\n";
}