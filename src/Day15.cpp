// --- Day 15: Beverage Bandits ---

#include "Day15.h"
#include "Tree.h"

// FIXME: make CharMatrix and inherit these.
void Dungeon::initialize(std::vector<std::string> Lines) {
  fill(' ');
  for (size_t i = 0, e = Lines.size(); i < e; ++i) {
    for (size_t j = 0, ee = Lines[i].size(); j < ee; ++j) {
      char Ch = Lines[i][j];
      insert(Ch, Coord(i, j));
      if (Ch == 'E' || Ch == 'G') {
        Creatures.emplace_back(Creature(Ch, Coord(i, j)));
      }
    }
  }
}

std::vector<Coord> Dungeon::getNeighbours(Coord Pos) {
  std::vector<Coord> Neighbours;
  for (auto N : std::vector<Coord>{Coord(Pos.x - 1, Pos.y),  /// N,E,S,W
                                   Coord(Pos.x, Pos.y + 1),
                                   Coord(Pos.x + 1, Pos.y),
                                   Coord(Pos.x, Pos.y - 1)}) {
    if (getValue(N) != '#') {
      Neighbours.emplace_back(N);
    }
  }
  return Neighbours;
}


// go through the neighbours, incrementally adding them until we find the target. 
// Recurse back from it until we find the direction to go to.
bool Dungeon::findTarget(Coord C, char Target, Direction &FirstStep, std::unordered_set<Coord, /* hash= */ Coord> Visited) {
//  char Target = (Race == 'E') ? 'G' : 'E';  // Race != Target is enough
  Visited.insert(C);
  C.dump();
  // go through neighbours until you find the target.
  for (Coord Nbor : getNeighbours(C)) {
    // for each location, check it and add it at the end of the queue.
    if (Visited.count(Nbor)) {
      continue;
    }
    if (getValue(Nbor) == Target) {
      std::cout << "found the target, it is "; Nbor.dump();
      return true;  // asserting Nbors are sorted and this is the correct Nbor..
    } else if (getValue(Nbor) == 'G' || getValue(Nbor) == 'E') { // colleague, don't follow.
      continue;
    } else {
      std::cout << getValue(Nbor) << "\n";
      assert(getValue(Nbor) == '.');
    }
    std::cout << "In: "; C.dump();
    std::cout << "     Nbor: "; Nbor.dump();
    // only save the first step, rest of the path is not necessary.
    if (FirstStep == Direction::INVALID) {
      if (Nbor.x < C.x)
        FirstStep = Direction::EAST;
      else if (C.x < Nbor.x)
        FirstStep = Direction::WEST;
      else if (Nbor.y < C.y)
        FirstStep = Direction::NORTH;
      else if (C.y < Nbor.y)
        FirstStep = Direction::SOUTH;
    }
    /// BFS
    if (findTarget(Nbor, Target, FirstStep, Visited)) {
      std::cout << "FOUND ( "; Nbor.dump(); std::cout << ")\n";
      return true;
    }
  }
  return false;
}

///
void move(Creature C, Direction Dir) {
  
}

/// One round of the Fight, all Creatures perform one movement or attack.
void Day15::tick() {
  // reading order:
  std::sort(Cave.Creatures.begin(), Cave.Creatures.end());  
  for (auto C : Cave.Creatures) {
    char Target = (C.Race == 'E') ? 'G' : 'E';
    Direction Step = Direction::INVALID;
    std::unordered_set<Coord, Coord> Visited;
    // TODO: is any target directly in range?
    Cave.findTarget(C.Position, Target, Step, Visited);
    Cave.move(C, Step);
    std::cout << "DONE!\n\n\n";
    return; // let's go just once.
  }
}

/// Fight till the battle is over.
void Day15::fight() {
  for (int i = 0; i < 2; ++i) {
    tick();
    Cave.dump();
  }
}


void Day15::solvePart1() {
  std::vector<std::string> Lines = Util::getLines("inputs/input_15_test.txt");
  Cave = Dungeon(Lines.size(), Lines[0].size());
  Cave.initialize(Lines);
  Cave.dump();
  fight();
  std::cout << -1 << "\n";
}

void Day15::solvePart2() {
  std::cout << -1 << "\n";
}

