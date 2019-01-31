// --- Day 15: Beverage Bandits ---

#include "Day15.h"
#include "Tree.h"

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

/// Create a new Dungeon with numbers instead of empty spaces, indicating the distance from the closest enemy.
/// Unit can then simply browse through directions and choose closest enemy available.
/// Go through all the units.
/// For each U, add its Coord to the map as zero.
/// Then, add each of its neighbours with incrementing distance.
/// Continue until you run out of neighbours.
void Dungeon::mapEnemies(char EnemyRace) {
  std::map<Coord, int>
      &Distances = (EnemyRace == 'G') ? ElfDistances : GobDistances;
  Distances.clear();
  // Add each enemy as a 0 distance.
  int Distance = 0;
  char Race = (EnemyRace == 'E') ? 'G' : 'E';
  // All live units, set to distance 0
  for (auto U : Units) {
    if (U.Health <= 0 || U.Race == Race)  // ignore friends and dead.
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
        if (Distances.count(Nbor) == 0) {
          if (getValue(Nbor) == '.') {
            Nbors.emplace_back(Nbor);
          }
        }
      }
    }
    if (Nbors.empty())
      break;
    Distance++;
    // Now that we've found the Nbors we have, let's add them to the map with Distance++
    for (auto N : Nbors) {
      Distances[N] = Distance;
    }
  } while (true);
}

void Dungeon::move(Unit &U) {
  // find Direction to go to.
  auto DirMap = (U.Race == 'E') ? ElfDistances : GobDistances;
  std::pair<Direction, int> Min = {Direction::INVALID, 1000000};
  for (auto D : std::vector<Direction>({NORTH, WEST, EAST, SOUTH})) {
    Coord NborPosition = Coord(U.Position.x + Move[D].first, U.Position.y + Move[D].second);
    if (DirMap.count(NborPosition)) {
      // '>' to keep the first min if there's more equally distant positions.
      if (Min.second > DirMap[NborPosition]) {
        Min = {D, DirMap[NborPosition]};
      }
    }
  }
  Direction Dir = Min.first;
  if (Dir == Direction::INVALID) {
    return;
  }
  // if already in the position of attack, don't move:
  if (Min.second == 0)
    return;

  // rest of the old function, clean me up:
  Coord Pos = U.Position;
  Coord NewPos = Coord(Pos.x + Move[Dir].first, Pos.y + Move[Dir].second);
  char Val = getValue(Pos);
  U.Position = NewPos;
  insert(Val, NewPos);
  insert('.', Pos);
}

bool Dungeon::attack(Unit U, bool &GameOver) {
  std::pair<Unit *, int> MinHPUnit = {nullptr, 1000000};

  for (auto D : std::vector<Direction>({NORTH, WEST, EAST, SOUTH})) {
    Coord Nbor = Coord(U.Position.x + Move[D].first, U.Position.y + Move[D].second);
    if ((U.Race == 'E' && getValue(Nbor) == 'G')
        || (U.Race == 'G' && getValue(Nbor) == 'E')) {
      Unit *Attacked = getUnit(Nbor);
      if (!MinHPUnit.first || (MinHPUnit.first->Health > Attacked->Health
          && Attacked->Health > 0))
        MinHPUnit = {Attacked, Attacked->Health};
    }
  }
  if (MinHPUnit.first) {
    int AttackPower = (U.Race == 'E') ? ElfPower : 3;
    MinHPUnit.first->Health -= AttackPower;
    if (MinHPUnit.first->Health < 0) {
      insert('.', MinHPUnit.first->Position);
      GameOver = checkWinner();
    }
    return true;
  }
  return false;
}

/// One round of the Fight, all Creatures perform one movement or attack.
bool Day15::tick() {
  // reading order:
  std::sort(Cave.Units.begin(), Cave.Units.end());

  bool GameOver = false;
  for (auto &U : Cave.Units) {
    if (Cave.checkWinner())
      return false;
    if (U.Health <= 0)
      continue;
    if (U.Race == 'G') {
      Cave.mapEnemies('E');
    } else {
      Cave.mapEnemies('G');
    }
    Cave.move(U);
    Cave.attack(U, GameOver);
  }
  return true;
}

/// Fight till the battle is over.
void Day15::fight() {
  int round = 0;
  while (tick()) {
    round++;
  }
  std::cout << round * Cave.sumHP() << "\n";
}

void Day15::solvePart1() {
  std::vector<std::string> Lines = Util::getLines("inputs/input_15.txt");
  Cave = Dungeon(Lines.size(), Lines[0].size());
  Cave.initialize(Lines);
  fight();
}

void Day15::solvePart2() {
  /// Empirically test to be the lowest where elves win:
  int ElfPower = 11;

  std::vector<std::string> Lines = Util::getLines("inputs/input_15.txt");

  Cave = Dungeon(Lines.size(), Lines[0].size(), ElfPower);
  Cave.initialize(Lines);
  fight();
}

