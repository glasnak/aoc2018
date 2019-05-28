// --- Day 22: Mode Maze ---

#include "Day22.h"


/// sum risks in a rectangle from 0 to Target
int Day22::sumCave() {
  int Sum = 0;
  for (int i = 0; i <= CAVE_TARGET.x; ++i) {
    for (int j = 0; j <= CAVE_TARGET.y; ++j) {
      Day22::RegionType RT = Cave.getValue(Coord(i,j)).Type;
      Sum += RT;
    }
  }
  return Sum;
}


// generate cave:
// Geologic index:
//    [X,0] = X * 16807
//    [0,Y] = Y * 48271
//    [X,Y] = Erosion[X-1, Y] * Erosion [X, Y-1]
// Erosion level:
//    Type = RegionType [Erosion % 3]
//    [X,Y] = GeoIndex + DEPTH
void Day22::generate() {
  Cave = Matrix<Day22::Region>(CAVE_SIZE.x, CAVE_SIZE.y);
  // FIXME: probably unnecessary initialization here
  long Geo = 0; 
  Region R = Region{RegionType::INVALID_TYPE, 0, Geo};
  Cave.fill(R);
  // Loop until reaching the Target while applying rules. Do this once.
  // initialize first column
  for (unsigned j = 0; j < Cave.Columns; ++j) {
    Cave.insert(Region{j * 16807}, Coord(0, j));
  }

  for (unsigned i = 1; i < Cave.Rows; ++i) {
    Cave.insert(Region{i * 48271}, Coord(i, 0));
  }
  // note that [0,0] is already filled and skipped here:

  long EroLeft, EroUp;
  for (unsigned i = 1; i < Cave.Rows; ++i) {
    for (unsigned j = 1; j < Cave.Columns; ++j) {
      if (Coord(i,j) == CAVE_TARGET) {
        Cave.insert(Region{0}, CAVE_TARGET);
      } else {
        // [X,Y] = Erosion[X-1, Y] * Erosion [X, Y-1]
        EroLeft = Cave.getValue(Coord(i - 1, j)).EroLevel;
        EroUp = Cave.getValue(Coord(i, j - 1)).EroLevel;
        Cave.insert(Region{EroLeft * EroUp}, Coord(i, j));
      }
    }
  }
}

void Day22::solvePart1() {
  generate();
//  if (TESTING)
//    dumpCave();
  std::cout << sumCave() << "\n";
}

void Day22::solvePart2() {  // 1029
  
  // invalid combos are (1,0), (2,1), (0,2), so:
  auto canMove = [](RegionType Region, ToolType Tool) {
    assert(Region != RegionType::INVALID_TYPE);
    assert(Tool != ToolType::INVALID_TOOL);
    return (Tool != (Region + 2) % 3);
  };
  
  struct Node {
    Node(int d, ToolType tool, Coord pos) : Dist(d), Tool(tool), Pos(pos) {}
    bool operator>(const Node &rhs) const {
      return (Dist > rhs.Dist);
    }
    int Dist;
    ToolType Tool;
    Coord Pos;
    void dump() {
      std::cout << "Node: D=" << Dist << " with " << Tool << " at (" << Pos.x << "," << Pos.y << ")\n";
    }
  };
  
  auto Distances = Matrix<int>(CAVE_SIZE.x, CAVE_SIZE.y);
  Distances.fill(20000);  // should be enough
  
  // A priority queue to order Distance - Coord pairs in decreasing order.
  // Or is it "what you have equipped" number? Hmm. Let's find out.
  std::priority_queue<Node, std::vector<Node>, std::greater<>> Dijkstra;

  // torch = 0, gear = 1, neither = 2
  Node N = Node(0, ToolType::TORCH, Coord(0,0));
  Dijkstra.push(N);
  Distances.insert(0, Coord(0,0));
  std::set<std::pair<Coord, ToolType>> Visited;
  
  while (!Dijkstra.empty()) {
    auto CurrentNode = Dijkstra.top(); 
    Dijkstra.pop();

    // Are we at the target with the torch equipped?
    if (CurrentNode.Pos == CAVE_TARGET) {
      int FinalDest = Distances.getValue(CurrentNode.Pos);
      if (CurrentNode.Tool != ToolType::TORCH)
        FinalDest += 7;
      std::cout << FinalDest << "\n";
      break;
    }

    // Is this already visited with smaller distance?
    if (CurrentNode.Dist > Distances.getValue(CurrentNode.Pos))
      continue;

    if (Visited.count({CurrentNode.Pos, CurrentNode.Tool}))
      continue;
    Visited.insert({CurrentNode.Pos, CurrentNode.Tool});

    std::vector<Direction> Dirs = {NORTH, WEST, EAST, SOUTH};
    for (const auto Dir : Dirs) {
      Coord Nbor = Coord(CurrentNode.Pos.x + Move[Dir].first, CurrentNode.Pos.y + Move[Dir].second);
      // Not within the cave?
      if (!Distances.isInRange(Nbor))
        continue;
      if (canMove(Cave.getValue(Nbor).Type, CurrentNode.Tool)) {
        int NewDist = Distances.getValue(CurrentNode.Pos) + 1;
        Node NextNode = Node(NewDist, CurrentNode.Tool, Nbor);
        if (!Visited.count({CurrentNode.Pos, CurrentNode.Tool}) || Distances.getValue(Nbor) >= NewDist) {
          Distances.insert(NewDist, Nbor);
          Dijkstra.push(NextNode);
        }
      } else {  // Can't move there. Move anyway, with changed tool:
        int NewDist = Distances.getValue(CurrentNode.Pos) + 7 + 1;
        int Region = (int) Cave.getValue(CurrentNode.Pos).Type;
        // change the tool:
        int NewTool;
        if (Region == CurrentNode.Tool) {
          NewTool = (Region + 1) % 3;
        } else {
          NewTool = Region;
        }
        Node NextNode = Node(NewDist, static_cast<ToolType>(NewTool), Nbor);
        if (!Visited.count({CurrentNode.Pos, CurrentNode.Tool}) || Distances.getValue(Nbor) >= NewDist) {
          Distances.insert(NewDist, Nbor);
          Dijkstra.push(NextNode);
        }
      }
    }
  }
}
