// --- Day 11: Chronal Charge ---

#include "Day11.h"

void Day11::fillGrid(const unsigned GridSize,
                               const unsigned SerialNumber) {
  Grid = Matrix<long>(GridSize, GridSize);
  Grid.fill(0);
  unsigned AdjustedSerialNumber = SerialNumber % 1000;
  long Val = 0;
  for (unsigned x = 1; x < GridSize + 1; ++x) {
    unsigned long SNx10 = AdjustedSerialNumber * (x + 10);
    unsigned long xxExpr = x * x + x * 20 + 100;
    for (unsigned y = 1; y < GridSize + 1; ++y) {
      // Val = ((10+x)*y + AdjustedSerialNumber) * (x+10);
      /// (10y + xy + SN) * (x + 10)
      /// (10xy + xxy + xSN) + (100y + 10xy + 10*SN)
      /// xxy + 20xy + SNx + 100y + 10*SN ?
      /// Val = xx*y + x20*y + SNx + 100*y + SN10;
      /// Val = y*xxExpr + SNx10;
      Val = ((y * xxExpr + SNx10) / 100) % 10 - 5;
      Grid.insert(Val, Coord(x - 1, y - 1));
    }
  }
}

Matrix<long> Day11::sumGrid(const unsigned SquareSize) {
  unsigned GridSize = Grid.Columns - SquareSize + 1;
  Matrix<long> GridCounts = Matrix<long>(GridSize - 2, GridSize - 2);
  GridCounts.fill(0);
  long Sum = 0;
  for (unsigned i = 0; i < GridCounts.Columns; ++i) {
    for (unsigned j = 0; j < GridCounts.Rows; ++j) {
      for (unsigned ii = i; ii < i + SquareSize; ++ii) {
        for (unsigned jj = j; jj < j + SquareSize; ++jj) { // terribly sllooww
          Sum += Grid.getValue(Coord(ii, jj));
        }
      }
      GridCounts.insert(Sum, Coord(i,j));
      Sum = 0;
    }
  }
  return GridCounts;
}

void Day11::solvePart1() {
  fillGrid(GridSize, SerialNumber);

  Matrix<long> GridCounts = sumGrid(/*squaresize = */ 3);
  long MaxElem;
  Coord MaxElemCoord = GridCounts.findMaxElement(MaxElem);
  std::cout << MaxElemCoord.x + 1 << "," << MaxElemCoord.y + 1 << "\n";
}

void Day11::solvePart2() {
  long MaxElem = std::numeric_limits<long>::min();
  Coord MaxElemCoord;
  unsigned BestSize = 0;

  // Statistically, most numbers in this (for our purposes, stochastic) grid are
  // negative, so the square won't be very large.
  // Plus, Each square can be in range of [x%10]-5 == {0..9}-5 == {-5..4}, so.
  // We also saw in part1 that max(3x3) is 29, which is more than max(2x2)=16;
  unsigned GridMaxSquare = (GridSize > 50) ? 50 : GridSize;
  for (unsigned i = 3; i < GridMaxSquare; ++i) {
    Matrix<long> GridCounts = sumGrid(i);
    long ThisMaxElem;
    Coord ThisMaxElemCoord;
    ThisMaxElemCoord = GridCounts.findMaxElement(ThisMaxElem);
    if (ThisMaxElem > MaxElem) {
      MaxElem = ThisMaxElem;
      MaxElemCoord = ThisMaxElemCoord;
      BestSize = i;
    }
  }
  std::cout << MaxElemCoord.x + 1 << "," << MaxElemCoord.y + 1 << ","
            << BestSize << "\n";
}
