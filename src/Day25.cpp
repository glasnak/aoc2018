// --- Day 25: Four-Dimensional Adventure ---

#include "Day25.h"

void Day25::solvePart1() {
//  std::vector<std::string> Lines = Util::getLines("inputs/input_25_test.txt");
  std::vector<std::string> Lines = Util::getLines("inputs/input_25.txt");
  Coord4D C;
  std::vector<std::vector<Coord4D>> Constellations;
  for (auto &Line : Lines) {
    sscanf(Line.c_str(), "%d,%d,%d,%d", &C.x, &C.y, &C.z, &C.t);
    int Master = -1;
    for (size_t i = 0; i < Constellations.size(); ++i) {
      for (auto &Star : Constellations[i]) {
        if (Star.distance(C) <= 3) {
          if (Master == -1) {
            Constellations[i].emplace_back(C);
            Master = i;
          } else {
            // Merge constellations, erase the second one:
            Constellations[Master].insert(Constellations[Master].end(),
                                          Constellations[i].begin(),
                                          Constellations[i].end());
            Constellations.erase(Constellations.begin() + i);
            --i;
          }
          break;
        }
      }
    }
    // Doesn't belong. Insert a new constellation.
    if (Master == -1) {
      Constellations.emplace_back();
      Constellations.back().push_back(C);
    }
  }
  std::cout << Constellations.size() << "\n";
}

/// There's no part 2 for day25:
void Day25::solvePart2() {
  std::cout << 0 << "\n";
}


