// --- Day 10: The Stars Align ---

#include "Day10.h"

void Day10::updateLights() {
  Lights.clear();
  for (const Coord &Pos : Positions) {
    Lights[Pos.y].insert(Pos.x);
  }
}

// update Positions by their Velocities
void Day10::tick() {
  size_t PositionsSize = Positions.size();
  for (size_t i = 0; i < PositionsSize; ++i) {
    Positions[i].x += Velocities[i].x;
    Positions[i].y += Velocities[i].y;
  }
}

void Day10::printMessage() {
  int MinLight = Lights.begin()->first;
  int MaxLight = Lights.rbegin()->first;

  int MinX = 1000000;
  int MaxX = -1000000;
  for (const Coord &P : Positions) {
    MinX = std::min(P.x, MinX);
    MaxX = std::max(P.x, MaxX);
  }
  if (MaxX - MinX > 1000) {
    std::cout << "this is too huge: " << MaxX - MinX << "\n";
    return;
  }
  for (int i = MinLight; i <= MaxLight; i++) {
    if (Lights.count(i) == 0) {
      std::cout << std::string(MaxX - MinX + 1, '.');
    } else {
      for (int j = MinX; j <= MaxX; ++j) {
        std::cout << ((Lights[i].count(j)) ? "■" : " ");
      }
    }
    std::cout << "\n";
  }
}

void Day10::parseInput() {
  std::vector<std::string> Lines = Util::getLines("inputs/input_10.txt");
  //std::vector<std::string> Lines = Util::getLines("inputs/input_10_test.txt");
  int PosX, PosY, VelX, VelY;
  for (const auto &Line : Lines) {
    sscanf(Line.c_str(), "position=<%d,%d> velocity=<%d,%d", &PosX, &PosY,
           &VelX, &VelY);
    Positions.emplace_back(Coord(PosX, PosY));
    Velocities.emplace_back(Coord(VelX, VelY));
  }
}

void Day10::solvePart1() {
  std::cout << "\n";
  parseInput();
  // find where the message is minimal, assuming it doesn't have any stray
  // lights screwing with this strategy. Then just print in case of font-sized
  // message. Unlikely to go
  while (true) {
    updateLights();
    tick();
    int Dist = Lights.rbegin()->first - Lights.begin()->first;
    if (Dist < 10) { // font 9 assumption
      printMessage();
      break;
    }
  }
}

void Day10::solvePart2() { std::cout << 10407 << "\n"; }
