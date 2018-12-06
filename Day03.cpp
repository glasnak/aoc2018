// --- Day 3: No Matter How You Slice It ---

#include "Day03.h"

void Day03::solvePart1() {
  // Strings = Util::getLines("inputs/input_03_test.txt");
  Strings = Util::getLines("inputs/input_03.txt");
  for (const auto &Str : Strings) {
    Areas.emplace_back(Area(Str));
  }
  for (unsigned i = 0; i < Areas.size(); ++i) {
    for (unsigned j = i + 1; j < Areas.size(); ++j) {
      if (areasOverlap(Areas[i], Areas[j])) {
        Areas[i].Overlaps = true;
        Areas[j].Overlaps = true;
      }
    }
  }
  std::cout << Overlappers.size() << "\n";
}

static bool valueInRange(int value, int min, int max) {
  return (value >= min) && (value < max);
}

void Day03::addOverlappers(Coord TopLeft, Coord BottomRight) {
  for (int y = TopLeft.y; y < BottomRight.y; ++y) {
    for (int x = TopLeft.x; x < BottomRight.x; ++x) {
      Coord ToInsert = Coord(x,y);
      Overlappers.emplace(ToInsert);
    }
  }
}

// find if areas overlap. Adds those
bool Day03::areasOverlap(Area &A, Area &B) {
  bool xOverlapA = valueInRange(A.Pos.x, B.Pos.x, B.Pos.x + B.Size.x);
  bool xOverlapB = valueInRange(B.Pos.x, A.Pos.x, A.Pos.x + A.Size.x);
  bool xOverlap = xOverlapA || xOverlapB;
 
  bool yOverlapA = valueInRange(A.Pos.y, B.Pos.y, B.Pos.y + B.Size.y);
  bool yOverlapB = valueInRange(B.Pos.y, A.Pos.y, A.Pos.y + A.Size.y);
  bool yOverlap = yOverlapA || yOverlapB;

  bool Overlap = xOverlap && yOverlap;
  if (Overlap) {
    int Top, Left, Bottom, Right;
    Left = std::max(A.Pos.x, B.Pos.x);
    Right = std::min(A.Pos.x + A.Size.x, B.Pos.x + B.Size.x);
    Top = std::max(A.Pos.y, B.Pos.y);
    Bottom = std::min(A.Pos.y + A.Size.y, B.Pos.y + B.Size.y);
    addOverlappers({Left, Top}, {Right, Bottom});
  }
  return Overlap;
}

// -------------------------------------------------------------

void Day03::solvePart2() {
  for (const auto &A : Areas) {
    if (!A.Overlaps) {
      std::cout << A.ID << "\n";
    }
  }
}
