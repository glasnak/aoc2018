// --- Day 15: Beverage Bandits ---

#include "Day15.h"
#include "Tree.h"

//#define DEBUG

// FIXME: make CharMatrix and inherit these.
void Dungeon::initialize(std::vector<std::string> Lines) {
  fill(' ');
  for (size_t i = 0, e = Lines.size(); i < e; ++i) {
    for (size_t j = 0, ee = Lines[i].size(); j < ee; ++j) {
      char Ch = Lines[i][j];
      insert(Ch, Coord(i, j));
      if (Ch == 'E' || Ch == 'G') {
        Units.emplace_back(Unit(Ch, Coord(i, j)));
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

//Direction getFirstStep(std::map<Coord, Direction> VisitedFrom, Coord C) {
//  // go through VisitedFrom from Coord and find the ultimate Source that has Direction::Invalid.
//  if (VisitedFrom[C] == Direction::INVALID) { // This is the first step.
//
//  }
//  return Direction::INVALID;
//}


/// Create a new Dungeon with numbers instead of empty spaces, indicating the distance from the closest enemy.
/// Unit can then simply browse through directions and choose closest enemy available.


/// Go through all the units.
/// For each U, add its Coord to the map as zero.
/// Then, add each of its neighbours with incrementing distance.
/// Continue until you run out of neighbours.
void Dungeon::mapEnemies(char EnemyRace) {
  std::map<Coord, int> &Distances = (EnemyRace == 'G') ? ElfDistances : GobDistances;
  Distances.clear();
  // Add each enemy as a 0 distance.
  int Distance = 0;
  for (auto U : Units) {
    if (U.Race != EnemyRace)
      continue;
    Distances[U.Position] = Distance;
  }
  do {
    // Now, get all the Neighbours.
    std::vector<Coord> Nbors;
    for (auto Pair : Distances) {
      if (Pair.second != Distance)
        continue;
      for (Coord Nbor : getNeighbours(Pair.first)) {
        if (getValue(Nbor) == '.' && Distances.count(Nbor) == 0)
          Nbors.emplace_back(Nbor);
      }
    }
    if (Nbors.empty())
      break;
    Distance++;
    // Now that we've found the Nbors we have, let's add them to the map with Distance=1
    for (auto N : Nbors) {
      Distances[N] = Distance;
    }
  } while (true);

#ifdef DEBUG
  for (unsigned i = 0; i < Rows; ++i) {
    for (unsigned j = 0; j < Columns; ++j) {
      if (Distances.count(Coord(i, j)))
        std::cout << Distances[Coord(i, j)];
      else
        std::cout << M[i][j];
    }
    std::cout << "\n";
  }
#endif
}

void Dungeon::move(Unit &U) {
  // find Direction to go to.
  auto DirMap = (U.Race == 'E') ? ElfDistances : GobDistances;
  std::pair<Direction, int> Min = {Direction::INVALID, 1000000};
  for (auto D : std::vector<Direction>({NORTH, WEST, EAST, SOUTH})) {
    Coord NborPosition = Coord(U.Position.x + Move[D].first, U.Position.y + Move[D].second);
    if (DirMap.count(NborPosition)) {
      if (Min.second > DirMap[NborPosition]) {  // '>': Keep the first min if there's more equally distant positions.
        Min = {D, DirMap[NborPosition]};
      }
    }
  }
  Direction Dir = Min.first;
  if (Dir == Direction::INVALID) {
    std::cout << "Unit " << U.Race << " can't move from "; U.Position.dump();
    return;
  }

  // rest of the old function, clean me up:
  Coord Pos = U.Position;
  Coord NewPos = Coord(Pos.x + Move[Dir].first, Pos.y + Move[Dir].second);
  char Val = getValue(Pos);
#ifdef DEBUG
  Pos.dump();
  std::cout << "     ->";
  NewPos.dump();
  std::cout << "moving to [" << getValue(NewPos) << "]\n";
#endif
  assert(getValue(NewPos) == '.');  // for now.
  U.Position = NewPos;
  insert(Val, NewPos);
  insert('.', Pos);
}

bool Dungeon::attack(Unit U) {
  for (auto D : std::vector<Direction>({NORTH, WEST, EAST, SOUTH})) {
    Coord Nbor = Coord(U.Position.x + Move[D].first, U.Position.y + Move[D].second);
    if ((U.Race == 'E' && getValue(Nbor) == 'G') || (U.Race == 'G' && getValue(Nbor) == 'E')) {
      return true;
    }
  }
  return false;
}

/// One round of the Fight, all Creatures perform one movement or attack.
void Day15::tick() {
  // reading order:
  std::sort(Cave.Units.begin(), Cave.Units.end());

//  int counter = 0;

  for (auto &U : Cave.Units) {
    Cave.mapEnemies('G');
    Cave.mapEnemies('E');
    // TODO: is any target directly in range? Attack if so.
    if (!Cave.attack(U))
      Cave.move(U);
//    std::cout << "Done with step.\n\n";
//    if (++counter > 4)
//      return; // let's go just once.
  }
}

/// Fight till the battle is over.
void Day15::fight() {
  for (int i = 0; i < 5; ++i) {
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

