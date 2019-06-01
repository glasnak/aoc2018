// --- Day 23: Experimental Emergency Teleportation  ---

#include "Day23.h"

Day23::PointSet Day23::parse() {
//  std::vector<std::string> Lines = Util::getLines("inputs/input_23_test2.txt");
  std::vector<std::string> Lines = Util::getLines("inputs/input_23.txt");
  Coord3D Pos;
  int radius;
  for (const auto &Line : Lines) {
    sscanf(Line.c_str(), "pos=<%d,%d,%d>, r=%d", &Pos.x,&Pos.y,&Pos.z,&radius);
    Points.emplace_back(std::make_pair(Pos, radius));
  }
  return Points;
}


void Day23::solvePart1() {
  /// Get the set of <Point, Radius>
  auto Points = parse();

  /// Find largest radius point:
  auto findMax = [&Points]() {
    auto maxPoint = std::make_pair(Coord3D(-1,-1,-1), 0);
    for (const auto &P : Points) {
      if (P.second > maxPoint.second) 
        maxPoint = P;
    }
    return maxPoint;
  };
  auto MaxPoint = findMax();
  
  /// Calc. manhattan distance:
  auto manhattan = [](const Coord3D C1, const Coord3D &C2) {
    return std::abs(C1.x - C2.x) + std::abs(C1.y - C2.y) + std::abs(C1.z - C2.z);
  };
  
  /// Count points within the radius of this point:
  auto countInRange = [&]() {
    int Count = 0;
    for (const auto &P : Points) {
      if (manhattan(P.first, MaxPoint.first) <= MaxPoint.second)
        Count++;
    }
    return Count;
  };
  std::cout << countInRange() << "\n";
}

void Day23::solvePart2() {
  std::cout << -1 << "\n";
}
