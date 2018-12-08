// --- Day 6: Chronal Coordinates ---

#include "Day06.h"

// for determining the size of matrix we need.
static Coord findMaxPoint(std::vector<Coord> Pts) {
    int MaxX = std::numeric_limits<int>::min();
    int MaxY = std::numeric_limits<int>::min();
    for (auto P : Pts) {
      MaxX = std::max(P.x, MaxX);
      MaxY = std::max(P.y, MaxY);
    }
    return {MaxX, MaxY};
}

// shift the points to get a different-sized matrix
void Day06::shiftPointsBy(int x, int y) {
  std::transform(std::begin(Points), std::end(Points), std::begin(Points),
                 [x, y](Coord xy) { return Coord(xy.x + x, xy.y + y); });
}

void Day06::initMatrix(const int Rows, const int Columns) {
  M = Matrix<int>(Rows, Columns);
  M.fill(-1);
  int Id = 0;
  for (auto P : Points) {
    M.insert(Id, Coord(P.x, P.y));
    Id++;
  }
}

std::map<int, int> Day06::countCells() {
  for (unsigned i = 0; i != M.Rows; ++i) {
    for (unsigned j = 0; j != M.Columns; ++j) {
      if (M.getValue(Coord(i, j)) == -1) {
        int Closest = findClosest(Coord(i, j));
        if (Closest >= 0)
          M.insert(Closest, Coord(i, j));
      }
    }
  }
  std::map<int, int> CellCounter;
  for (const auto &Row : M.get()) {
    for (const auto &Cell : Row) {
      CellCounter[Cell]++;
    }
  }
  return CellCounter;
}

void Day06::solvePart1() {
//  Points = Util::getCoord("inputs/input_06_test.txt");
  Points = Util::getCoord("inputs/input_06.txt");

  /// run with orig. Matrix first:
  Coord MaxPoint = findMaxPoint(Points);
  initMatrix(MaxPoint.x + 1, MaxPoint.y + 1);
  std::map<int,int> Cells1 = countCells();

  /// run with a slightly bigger matrix in all directions:
  shiftPointsBy(2, 3);
  initMatrix(MaxPoint.x + 5, MaxPoint.y + 6);
  std::map<int,int> Cells2 = countCells();
  int MaxRegion = 0;
  for (const auto &C : Cells2) {
    // finite regions only (same in both matrices):
    if (C.first >= 0 && Cells1[C.first] == C.second)
      MaxRegion = std::max(MaxRegion, C.second);
  }
  std::cout << MaxRegion << "\n";
}

static int calcDistance(Coord A, Coord B) {
  return std::abs(A.x - B.x) + std::abs(A.y - B.y);
}

int Day06::findClosest(Coord Cell) {
  int MinDistance = std::numeric_limits<int>::max();
  Coord ClosestPoint;
  bool Equidistant = false;

  for (const auto &P : Points) {
    int Distance = calcDistance(Cell, P);
    if (MinDistance > Distance) {
      MinDistance = Distance;
      ClosestPoint = P;
      Equidistant = false;
    } else if (MinDistance == Distance) {
      Equidistant = true;
    }
  }
  if (Equidistant)
    return -1;
  return M.getValue(ClosestPoint);
}


void Day06::solvePart2() {
  int RegionSize = 0;
  for (unsigned i = 0; i != M.Rows; ++i) {
    for (unsigned j = 0; j != M.Columns; ++j) {
      int SumDistances = 0;
      for (const auto &P : Points) {
        SumDistances += calcDistance(P, Coord(i,j));
      }
      if (SumDistances < 10000)
        RegionSize++;
    }
  }
  std::cout << RegionSize << "\n";
}
