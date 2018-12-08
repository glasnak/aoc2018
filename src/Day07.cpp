// --- Day 7: The Sum of Its Parts ---

#include "Day07.h"

std::vector<std::pair<char, char>> Day07::getInput() {
  std::vector<std::pair<char, char>> Inputs;
  //  std::vector<std::string> Lines =
  //  Util::getLines("inputs/input_07_test.txt");
  std::vector<std::string> Lines = Util::getLines("inputs/input_07.txt");
  for (const auto &Line : Lines) {
    char U, V;
    sscanf(Line.c_str(), "Step %c must be finished before step %c can begin.",
           &U, &V);
    Inputs.emplace_back(std::make_pair(U, V));
  }
  return Inputs;
}

void Day07::init() {
  Edges = getInput();
  for (const auto &E : Edges) {
    Src.insert(E.first);
    Dst.insert(E.second);
  }
  Letters.insert(Src.begin(), Src.end());
  Letters.insert(Dst.begin(), Dst.end());
}

void Day07::solvePart1() {
  init();
  std::string Result;
  std::vector<char> AvailableQueue;

  while (!Letters.empty()) {
    std::set_difference(Letters.begin(), Letters.end(), Dst.begin(), Dst.end(),
                        std::inserter(AvailableQueue, AvailableQueue.begin()));
    std::sort(AvailableQueue.begin(), AvailableQueue.end());
    Result += AvailableQueue[0];
    Letters.erase(AvailableQueue[0]);
    Dst.clear();
    for (const auto &E : Edges) {
      if (Result.find(E.first) != std::string::npos)
        continue;
      Dst.insert(E.second);
    }
    AvailableQueue.clear();
  }
  std::cout << Result << "\n";
}

void Day07::solvePart2() {
  init();
  unsigned NumWorkers = 5;
  int BaseTimeSpent = 60;
  std::string Result;
  std::map<char, int> TimeLeft;

  for (auto L : Letters) {
    TimeLeft[L] = BaseTimeSpent + (L - 'A') + 1;
  }
  std::vector<char> InProgress;
  std::deque<char> AvailableQueue;

  for (int Sec = 0; Sec < 10000; ++Sec) {
    /// Find what's available:
    std::set_difference(Letters.begin(), Letters.end(), Dst.begin(), Dst.end(),
                        std::inserter(AvailableQueue, AvailableQueue.begin()));
    std::sort(AvailableQueue.begin(), AvailableQueue.end());
    /// Update InProgress <<< AvailableQueue;
    while (InProgress.size() < NumWorkers && !AvailableQueue.empty()) {
      char Letter = AvailableQueue.front();
      InProgress.emplace_back(Letter);
      AvailableQueue.pop_front();
      Letters.erase(Letter);
    }
    /// for each InProgress, decrement each TimeLeft. If it's zero, remove it.
    InProgress.erase(
        std::remove_if(InProgress.begin(), InProgress.end(),
                       [&TimeLeft](char C) { return (--TimeLeft[C] == 0); }),
        InProgress.end());
    /// add each TimeLeft that left InProgress to Result. FIXME: This is ugly af
    for (const auto &Times : TimeLeft) {
      if (Times.second == 0 && Result.find(Times.first) == std::string::npos) {
        Result += Times.first;
      }
    }

    bool Finish = true;
    for (auto T : TimeLeft) {
      if (T.second != 0) {
        Finish = false;
        break;
      }
    }
    if (Finish) {
      std::cout << Sec + 1 << "\n";
      return;
    }

    // recompute availability...
    Dst.clear();
    for (const auto &E : Edges) {
      if (Result.find(E.first) != std::string::npos)
        continue;
      Dst.insert(E.second);
    }
    AvailableQueue.clear();
  }
}
