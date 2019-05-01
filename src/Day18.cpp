// --- Day 18: Settlers of The North Pole ---

#include "Day18.h"

static const bool TESTING = false;


/// Create grid out of input.
void Day18::parse(const std::vector<std::string> &Lines) {
  Grid.fill('.');
  for (size_t i = 0, e = Lines.size(); i < e; ++i) {
    for (size_t j = 0, ee = Lines[i].size(); j < ee; ++j) {
      Grid.insert(Lines[i][j], Coord(i, j));
    }
  }
}

/// create new Grid and replace the old one with it.
Matrix<char> Day18::step(const Matrix<char> &OldGrid) {
  /// open ground (.), trees (|), or a lumberyard (#)
  /// Rules for this Cellular Automaton:
  //      1.  . => |   IF   3 or more '|' neighbours
  //      2.  | => #   IF   3 or more '#' neighbours
  //      3.  # => #   IF   1 or more '#' AND 1 or more '|' neighbours
  // alternatively:       
  //      3.  # => .   IF   only '.' neighbours.
  Matrix<char> NewGrid = Matrix<char>(OldGrid.Rows, OldGrid.Columns);
  NewGrid.fill('.');
  std::vector<char> Nbors;
  for (size_t i = 0, e = OldGrid.Columns; i < e; ++i) {
    for (size_t j = 0, ee = OldGrid.Rows; j < ee; ++j) {
      Nbors = OldGrid.getExtendedNeighboursOf(Coord(i, j));
      char Val = OldGrid.getValue(Coord(i, j));
      char NewVal = Val;
      switch (OldGrid.getValue(Coord(i, j))) {
      case '.':    //   . => |   IF   3 or more '|' neighbours
        if (std::count(Nbors.begin(), Nbors.end(), '|') > 2) {
          NewVal = '|';
        }
        break;
      case '|':    //   | => #   IF   3 or more '#' neighbours
        if (std::count(Nbors.begin(), Nbors.end(), '#') > 2) {
          NewVal = '#';
        }
        break;
      case '#':    //   # => .   IF   it only has '.' neighbours.
        if (std::count(Nbors.begin(), Nbors.end(), '|') == 0
            || std::count(Nbors.begin(), Nbors.end(), '#') == 0) {
          NewVal = '.';
        }
        break;
      default:
        assert(!"Invalid character in the grid.");
      }
      NewGrid.insert(NewVal, Coord(i, j));
    }
  }
  return NewGrid;
}

void Day18::solvePart1() {
  int GridSize = TESTING ? 10 : 50;
  std::string InputFile = TESTING ? "inputs/input_18_test.txt" : "inputs/input_18.txt";
  Grid = Matrix<char>(GridSize,GridSize);
  std::vector<std::string> Lines = Util::getLines(InputFile);
  parse(Lines);
  
  // step until idk when:
  for (int i = 0; i < 10; ++i) {
    if (TESTING) {
      Grid.dump("");
    }
    Grid = step(Grid);
  }
  if (TESTING) {
    Grid.dump("");
  }

  std::cout << Grid.count('#') * Grid.count('|') << "\n";
}

void Day18::solvePart2() {
  int GridSize = TESTING ? 10 : 50;
  std::string InputFile = TESTING ? "inputs/input_18_test.txt" : "inputs/input_18.txt";
  Grid = Matrix<char>(GridSize,GridSize);
  std::vector<std::string> Lines = Util::getLines(InputFile);
  parse(Lines);

  /// After an initial phase (~400 cycles), the same grid is repeated each 
  /// 28 cycles, so each (1,000,000,000 - N*28) works with the same result as 1B
  for (int i = 0; i < 440; ++i) {
    Grid = step(Grid);
  }
  std::cout << Grid.count('#') * Grid.count('|') << "\n";
}