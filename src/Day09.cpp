// --- Day 9: Marble Mania ---

#include "Day09.h"

static std::list<unsigned>::iterator
circularPrev(std::list<unsigned> &L, std::list<unsigned>::iterator &Iter) {
  return (Iter == L.begin()) ? std::prev(L.end()) : std::prev(Iter);
}

static std::list<unsigned>::iterator
circularNext(std::list<unsigned> &L, std::list<unsigned>::iterator &Iter) {
  // skip the std::begin because it's a circle and so equals std::end;
  return (Iter == L.end()) ? std::next(L.begin()) : std::next(Iter);
}

static void printLine(int Player, std::list<unsigned> Marbles) {
  std::cout << "[" << Player + 1 << "]  ";
  for (auto M : Marbles) {
    std::cout << M << "  ";
  }
  std::cout << "\n";
}

unsigned long Day09::play(const unsigned NumPlayers,
                          const unsigned LastMarbleWorth,
                          const unsigned WeirdestTurn) {
  std::vector<unsigned> Scores(NumPlayers, 0);
  std::list<unsigned> Marbles;
  unsigned Player = 0;
  unsigned NextMarble = 0;
  auto Iter = Marbles.begin();
  Marbles.insert(Iter, 0);
  // Let's play!
  for (unsigned i = 1; i <= LastMarbleWorth; ++i) {
    if (i % WeirdestTurn == 0) {
      Scores[Player] += ++NextMarble;
      for (unsigned j = 0; j < 9; ++j)
        Iter = circularPrev(Marbles, Iter);
      Scores[Player] += *Iter;
      Iter = Marbles.erase(Iter);
      Iter = circularNext(Marbles, Iter);
    } else {
      Marbles.insert(Iter, ++NextMarble);
    }
    // printLine(Player, Marbles);

    Player = (Player + 1) % NumPlayers;
    Iter = circularNext(Marbles, Iter);
  }
  return *std::max_element(Scores.begin(), Scores.end());
}

/// 431 players; last marble is worth 70950*100 points
void Day09::solvePart1() { std::cout << play(431, 70950) << "\n"; }

/// 431 players; last marble is worth 70950*100 points
void Day09::solvePart2() {
  // Note: any bigger and Scores will need to be of unsigned long
  std::cout << play(431, 7095000) << "\n";
}
