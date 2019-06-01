// --- Day 23: Experimental Emergency Teleportation  ---

#include "Day23.h"
#include<z3++.h>


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
  auto Points = parse();
  z3::context Context;
  z3::expr x = Context.int_const("x");
  z3::expr y = Context.int_const("y");
  z3::expr z = Context.int_const("z");
  
  z3::expr_vector InRanges(Context);

  size_t NumPoints = Points.size();
  for (size_t i = 0; i < NumPoints; ++i) {
    std::string InRangeStr = "in_range_" + std::to_string(i);
    InRanges.push_back(Context.int_const(InRangeStr.c_str()));
  }
  auto RangeCount = Context.int_const("sum");

  z3::optimize Opt(Context);
  
  z3::expr One = Context.int_val(1);
  z3::expr Zero = Context.int_val(0);
  for (size_t i = 0; i < NumPoints; ++i) {
    std::pair<Coord3D, int> Nanobot = Points[i];

    /// Manhattan distance range constraint
    Opt.add(
        InRanges[i] ==
            z3::ite(
                ((z3::abs(x - Nanobot.first.x)
                    + z3::abs(y - Nanobot.first.y)
                    + z3::abs(z - Nanobot.first.z)
                ) <= Nanobot.second),
                One, Zero));
  }
  
  /// Nanobots within range, this will be maximized.
  Opt.add(RangeCount == z3::sum(InRanges));
  
  /// Second constraint - be closest to zero, this will be minimized as 
  /// a secondary constraint.
  auto DistFromZero = Context.int_const("dist");
  Opt.add(DistFromZero == z3::abs(x) + z3::abs(y) + z3::abs(z));

  z3::optimize::handle h1 = Opt.maximize(RangeCount);
  z3::optimize::handle h2 = Opt.minimize(DistFromZero);
  if (Opt.check() != z3::sat) {
    assert(!"Unsatisfiable constraints in Z3 solver!\n");
    exit(1);  // ?
  }
//  std::cout << "Satisfiable? " << Opt.check() << ".\n";
//  std::cout << "Range:" << Opt.lower(h1) << ",  " << Opt.upper(h1) << "\n";
//  std::cout << "DistFromZero:" << Opt.lower(h2) << ",  " << Opt.upper(h2) << "\n";
  std::cout << Opt.lower(h2) << "\n";
}
