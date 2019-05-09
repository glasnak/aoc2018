// --- Day 20: A Regular Map ---

#include "Day20.h"


static Matrix<char> initGrid(unsigned Size) {
  // Make size odd to have a clear centre.
  Size = (Size % 2 == 0) ? Size + 1 : Size;
  Matrix<char> Grid = Matrix<char>(Size, Size);
  Grid.fill('#');
  return Grid;
}


/// transform complicated regex to longer but simpler one that can draw a map
std::deque<char> removeBrackets(const std::deque<char> &Regex) {
  std::deque<char> NewRegex = Regex;
  while (true) {
    std::vector<std::vector<char>> Options;
    std::vector<char> Opt1, Opt2;
    // find last '(' to transform the last bracket option.
    auto RIter = std::find(NewRegex.rbegin(), NewRegex.rend(), '(');
    auto StartRange = RIter;
    if (RIter == NewRegex.rend())
      return NewRegex;
    
    // RIter is at '(', move forward and add options while you encounter '|', then end when you encounter ')'
    // Store whatever options are in between.
    int OptNum = 0;
    do { /// for all options found, e.g. (N|W|EW|NEWS|...)
      Options.emplace_back(std::vector<char>());
      RIter--;
      
      assert(RIter != NewRegex.rend());
      while (!Util::is_contained(")|^$", *RIter)) {
        Options[OptNum].emplace_back(*RIter);
        RIter--;
      }
      OptNum++;
      assert(OptNum < 5);
    } while (*RIter == '|');

    assert(*RIter == ')');
    RIter--;

    // Sort options first, so that we can reverse only the shortest ones and keep longest at the end.
      std::sort(Options.begin(), Options.end(), 
          [](const std::vector<char> & A, const std::vector<char> & B){ return A.size() < B.size(); });

    std::vector<char> NewOpt;
    while (Options.size() > 1) {
      NewOpt.insert(NewOpt.end(), Options[0].begin(), Options[0].end());
      for (auto It = Options[0].rbegin(); It != Options[0].rend(); It++) {
        switch (*It) {
        case 'N': NewOpt.emplace_back('S'); break;
        case 'E': NewOpt.emplace_back('W'); break;
        case 'S': NewOpt.emplace_back('N'); break;
        case 'W': NewOpt.emplace_back('E'); break;
        default: assert(!"what");
        }
      }
      Options.erase(Options.begin());
    }
    assert(Options.size() == 1);
    NewOpt.insert(NewOpt.end(), Options[0].begin(), Options[0].end());
    auto NewIter = NewRegex.erase(std::next(StartRange).base(), std::prev(RIter.base()));
    NewRegex.insert(NewIter, NewOpt.begin(), NewOpt.end());
  }
}

// parse the entire Regex and find all possible paths.
// assuming the most simple case first: ^WNE$, no braces.
void Day20::drawMap(const std::string &Regex, Coord InitPosition) {
  std::deque<char> RegexDeque;
  for (const auto &C : Regex) {
    RegexDeque.emplace_back(C);
  }
  auto NewRegex = removeBrackets(RegexDeque);
  Coord Pos = InitPosition;
  Coord NewPos;
  // get rid of '^'
  NewRegex.pop_front();
  char CurrentC = NewRegex.front();
  NewRegex.pop_front();
  while (CurrentC != '$') {
    // Simplest case. NWE.
    if (Util::is_contained("NESW", CurrentC)) {
      char DoorChar = (CurrentC == 'N' || CurrentC == 'S') ? '-' : '|';
      Direction Movement = Direction::INVALID;
      switch (CurrentC) {
      case 'N': Movement = Direction::NORTH;  break;
      case 'E': Movement = Direction::EAST;   break;
      case 'S': Movement = Direction::SOUTH;  break;
      case 'W': Movement = Direction::WEST;   break;
      default:
        assert(!"unreachable");
      }
      NewPos = Pos + Coord(Move[Movement]) * 2;
      if (Grid.isInRange(NewPos)) {
        // insert new door instead of '?'
        Grid.insert(DoorChar, Coord(Pos + Coord(Move[Movement])));
        Pos = NewPos;
        Grid.insert('.', Pos);
      }
    }
    CurrentC = NewRegex.front();
    NewRegex.pop_front();
  }
}

// finds neighbour-rooms
std::vector<Coord> Day20::getAdjacentRooms(Coord Room) {
  std::vector<Coord> AdjRooms;
  for (const auto Dir : std::vector<Direction>({NORTH, WEST, EAST, SOUTH})) {
    Coord DoorCell = Room + Coord(Move[Dir]);
    Coord NewPos = Room + Coord(Move[Dir]) * 2;
    bool Hodor = Grid.isInRange(DoorCell)
        && (Grid.getValue(DoorCell) == '|' || Grid.getValue(DoorCell) == '-');
    if (DistanceGrid.isInRange(NewPos) && Hodor
        && DistanceGrid.getValue(NewPos) == -1
        && Grid.getValue(NewPos) == '.') {
      AdjRooms.emplace_back(NewPos);
    }
  }
  return AdjRooms;
}

// Perform BFS, starting at X (exactly middle, x,y both even)
// fills a new Matrix with numbers indicating distance from the start.
int Day20::search(Coord InitPosition, unsigned GridSize) {
  std::deque<Coord> Reachable;
  Reachable.emplace_back(InitPosition);
  DistanceGrid = Matrix<int>(GridSize, GridSize);
  DistanceGrid.fill(-1);
  unsigned Distance = 0;
  while (!Reachable.empty()) {
    // for all reachable,
    auto NewReachable = std::deque<Coord>();
    DistanceGrid.insert(Distance, Reachable.front());
    for (const auto &Room : Reachable) {
      DistanceGrid.insert(Distance, Room);
      auto AdjRooms = getAdjacentRooms(Room);
      NewReachable.insert(NewReachable.end(), AdjRooms.begin(), AdjRooms.end());
    }
    Reachable.clear();
    Reachable = NewReachable;
    Distance++;
  }
  return Distance - 1;
}


void Day20::solvePart1() {
  std::string InputFile = "inputs/input_20.txt";
  std::string Regex = Util::getLines(InputFile)[0];
  unsigned GridSize = 203;
  Grid = initGrid(GridSize);
  Coord InitPosition = Coord(GridSize / 2 - 1, GridSize / 2 - 1);
  drawMap(Regex, InitPosition);
  Grid.insert('X', InitPosition);
  int Distance = search(InitPosition, GridSize);
  std::cout << Distance << "\n";
}

void Day20::solvePart2() {
  unsigned Count = 0;
  for (unsigned i = 0; i < DistanceGrid.Columns; ++i) {
    for (unsigned j = 0; j < DistanceGrid.Rows; ++j) {
      if (DistanceGrid.getValue(Coord(i,j)) >= 1000) {
        Count++;
      }
    }
  }
  std::cout << Count << "\n";
}

