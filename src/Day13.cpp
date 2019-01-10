// --- Day 13: Mine Cart Madness ---

#include "Day13.h"


void RailroadGrid::initialize(std::vector<std::string> Lines) {
  fill(' ');
  for (size_t i = 0, e = Lines.size(); i < e; ++i) {
    for (size_t j = 0, ee = Lines[i].size(); j < ee; ++j) {
      insert(Lines[i][j], Coord(i, j));
    }
  }
}

static bool isMineCart(char C) {
  return (C == '<' || C == 'v' || C == '^' || C == '>');
}

void RailroadGrid::advanceCart(MineCart &MC) {
  Coord NextCell;
  switch (MC.Facing) { /// S(1,0), N(-1,0), E(0,1), W(0,-1)
  case Direction::NORTH: NextCell = Coord(MC.Position.x-1, MC.Position.y  ); break;
  case Direction::EAST:  NextCell = Coord(MC.Position.x,   MC.Position.y+1); break;
  case Direction::SOUTH: NextCell = Coord(MC.Position.x+1, MC.Position.y  ); break;
  case Direction::WEST:  NextCell = Coord(MC.Position.x,   MC.Position.y-1); break;
  case Direction::INVALID: assert(false);
  }
  // N+/ => (E +1)   N+\ => (W -1)
  // E+/ => (N -1)   E+\ => (S +1)
  // S+/ => (W +1)   S+\ => (E -1)
  // W+/ => (S -1)   W+\ => (N +1)
  bool NorthSouth = (MC.Facing % 2 == 0);
  bool ForwardSlash = (getValue(NextCell) == '/');
  if (getValue(NextCell) == '/' || getValue(NextCell) == '\\') { // corner
    if (NorthSouth ^ ForwardSlash)
      MC.Facing = Direction((MC.Facing + 3) % 4);
    else
      MC.Facing = Direction((MC.Facing + 1) % 4);
  } else if (getValue(NextCell) == '+') { ///  - | + ... other minecarts;
    /// Each time a cart has the option to turn (by arriving at any
    /// intersection), it turns left the first time, goes straight the second
    /// time, turns right the third time, and then repeats those directions
    /// starting again with left the fourth time, straight the fifth time, and
    /// so on.
    MC.Facing = Direction((MC.Facing + MC.IntersectionDecision) % 4);
    switch (MC.IntersectionDecision) { // left(3) -> straight(0) -> right(1) -> left ...
    case 0:  MC.IntersectionDecision = 1;  break;
    case 1:  MC.IntersectionDecision = 3;  break;
    case 3:  MC.IntersectionDecision = 0;  break;
    default: assert(!"Unreachable.");
    }
  }
  MC.Position = NextCell;
}

/// move one step for all minecarts. Return false if collision happens.
bool RailroadGrid::tick(bool QuitOnCollision) {
  std::vector<MineCart> CollidedCarts;
  std::vector<Coord> Collisions;
  for (auto &MC : MineCarts) {
    advanceCart(MC);
    if (hasCollision(MC)) {
      if (QuitOnCollision) {
        std::cout << MC.Position.y << "," << MC.Position.x << "\n";
        return false;
      } else {
        Collisions.emplace_back(MC.Position);
        /// *might* be a triple collision for all I know:
        for (auto Cart : MineCarts) {
          if (Cart.Position == MC.Position)
            CollidedCarts.push_back(Cart);
        }
      }
    }
  }
  // remove MineCarts that collided in this tick:
  for (auto Cart : CollidedCarts) {
    MineCarts.erase(std::remove(MineCarts.begin(), MineCarts.end(), Cart),
                    MineCarts.end());
  }
  return CollidedCarts.empty();
}

/// clear Grid of the Mine Carts, so that we know what's beneath them.
/// Store them separately with
void RailroadGrid::clearGrid() {
  // Remove all <^v> and replace them with |-;
  // traverse the Grid first:
  // Note: this might be more complex if minecarts could start on crossroads.
  MineCarts.clear();
  int StartingId = 1000;
  for (size_t i = 0, e = Rows; i < e; ++i) {
    for (size_t j = 0, ee = Columns; j < ee; ++j) {
      Direction Dir;
      if (!isMineCart(M[i][j]))
        continue;
      switch (M[i][j]) {
      case '^':
        Dir = Direction::NORTH;
        M[i][j] = '|';
        break;
      case 'v':
        Dir = Direction::SOUTH;
        M[i][j] = '|';
        break;
      case '>':
        Dir = Direction::EAST;
        M[i][j] = '-';
        break;
      case '<':
        Dir = Direction::WEST;
        M[i][j] = '-';
        break;
      default:
        assert(!"Unreachable");
      }
      MineCarts.emplace_back(MineCart(StartingId++, Coord(i,j), Dir));
    }
  }
  std::sort(MineCarts.begin(),MineCarts.end());
}

bool RailroadGrid::hasCollision(MineCart CollidingCart) {
  for (auto MC : MineCarts) {
    if (MC.ID == CollidingCart.ID)
      continue;
    if (MC.Position == CollidingCart.Position) {
      return true;
    }
  }
  return false;
}

void Day13::parseInput() {
//   std::vector<std::string> Lines = Util::getLines("inputs/input_13_test2.txt");
  std::vector<std::string> Lines = Util::getLines("inputs/input_13.txt");
  Grid = RailroadGrid(Lines.size(), Lines[0].size());
  Grid.initialize(Lines);
  Grid.clearGrid();
}

// Find the position of a first collision.
void Day13::solvePart1() {
  parseInput();
  while (Grid.tick()) {}
}


// Find the Last Cart Standing.
void Day13::solvePart2() {
  parseInput();
  while (Grid.MineCarts.size() > 1) {
    Grid.tick(/*QuitOnCollision=*/false);
  }
  std::cout << Grid.MineCarts[0].Position.y << "," << Grid.MineCarts[0].Position.x << "\n";
}
