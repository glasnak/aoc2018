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
        Creatures.emplace_back(Unit(Ch, Coord(i, j)));
      }
    }
  }
}

std::vector<Coord> Dungeon::getNeighbours(Coord Pos) {
  std::vector<Coord> Neighbours;
  std::vector<Direction> Dirs = {NORTH, WEST, EAST, SOUTH};
  for (const auto Dir : Dirs) {
    Coord NewPos = Coord(Pos.x + Move[Dir].first, Pos.y + Move[Dir].second);
    if (getValue(NewPos) != '#') {
      Neighbours.emplace_back(NewPos);
    }
  }
  return Neighbours;
}

Direction getFirstStep(std::map<Coord, Direction> VisitedFrom, Coord C) {
  // go through VisitedFrom from Coord and find the ultimate Source that has Direction::Invalid.
  if (VisitedFrom[C] == Direction::INVALID) { // This is the first step.

  }
  return Direction::INVALID;
}

// go through the neighbours, incrementally adding them until we find the target. 
// Recurse back from it until we find the direction to go to.
//// FIXME Unit instead of C+Target;
bool Dungeon::findTarget(Coord C, char Target, Direction &FirstStep) {
//  char Target = (Race == 'E') ? 'G' : 'E';  // Race != Target is enough
//  std::unordered_set<Coord, /* hash= */ Coord> Visited;
//  Visited.insert(C);
  C.dump();
  std::map<Coord, Direction> VisitedFrom;
  VisitedFrom[C] = Direction::INVALID;
  // init Neighbor queue:
  Coord Source = C;
  std::deque<Coord> Neighbours;
  for (auto N : getNeighbours(Source)) {
    Neighbours.push_back(N);
  }

  auto CurrentNbors = getNeighbours(Source);
  // go through neighbours until you find the target.
  do {
    std::cout << "\n CHECKING OUT "; Source.dump();
    std::cout << "Neighbours (" << Neighbours.size() << "):\n";
    for (auto N : Neighbours) {
      N.dump();
    }
    auto Nbor = Neighbours.front();
    Neighbours.pop_front();

    // for each location, check it and add it at the end of the queue.
    if (VisitedFrom.count(Nbor)) {
      std::cout << "Already visited: "; Nbor.dump();
      continue;
    }
    if (VisitedFrom[Source] == Direction::INVALID) { /// This is the first step.
      if (Nbor.x < Source.x)
        VisitedFrom[Nbor] = Direction::NORTH;
      else if (Source.x < Nbor.x)
        VisitedFrom[Nbor] = Direction::SOUTH;
      else if (Nbor.y < Source.y)
        VisitedFrom[Nbor] = Direction::WEST;
      else if (Source.y < Nbor.y)
        VisitedFrom[Nbor] = Direction::EAST;
    } else { // not first step, follow the first anyway;
      VisitedFrom[Nbor] = VisitedFrom[Source];
    }
    if (getValue(Nbor) == Target) {   // enemy found
      std::cout << "Step to " << VisitedFrom[Nbor] << "\n";
      // FIXME just return this instead
      FirstStep = VisitedFrom[Nbor];
      return true;
    } else if (getValue(Nbor) == 'G' || getValue(Nbor) == 'E') {
      continue;
    } else {
      assert(getValue(Nbor) == '.' && "");
    }
    // Setup for next:

    Source = Nbor;
    for (auto N : getNeighbours(Source)) {
      if (VisitedFrom.count(N) == 0)
        if (std::find(Neighbours.begin(), Neighbours.end(), N) == Neighbours.end())
          Neighbours.push_back(N);
    }
  } while (!Neighbours.empty());
  return false;
}

void Dungeon::move(Unit C, Direction Dir) {
  std::cout << "trying to move to " << Dir << "\n";
  Coord Pos = C.Position;
  if (Dir == Direction::INVALID)
    assert(!"Invalid direction!\n");
  Coord NewPos = Coord(Pos.x + Move[Dir].first, Pos.y + Move[Dir].second);
  char Val = getValue(Pos);
  Pos.dump();
  NewPos.dump();
  std::cout << "moving to " << getValue(NewPos) << "\n";
  assert(getValue(NewPos) == '.'); // for now.
  insert(Val, NewPos);
  insert('.', Pos);
}

/// One round of the Fight, all Creatures perform one movement or attack.
void Day15::tick() {
  // reading order:
  std::sort(Cave.Creatures.begin(), Cave.Creatures.end());

  for (auto C : Cave.Creatures) {
    C.Position.dump();
    char Target = (C.Race == 'E') ? 'G' : 'E';
    Direction Step = Direction::INVALID;
    // TODO: is any target directly in range?
    Cave.findTarget(C.Position, Target, Step);
    Cave.move(C, Step);
    std::cout << "Done with step.\n\n";
    return; // let's go just once.
  }
}

/// Fight till the battle is over.
void Day15::fight() {
  //for (int i = 0; i < 2; ++i) {
  tick();
  Cave.dump();
  //}
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

