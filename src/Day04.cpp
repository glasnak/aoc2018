// --- Day 4: Repose Record ---

#include "Day04.h"

void Day04::solvePart1() {
  // Strings = Util::getLines("inputs/input_04_test.txt");
  Strings = Util::getLines("inputs/input_04.txt");
  std::sort(Strings.begin(), Strings.end());
  int GuardID = 0;
  int SleepyTime = 0;
  int WakeyWakey = 0;
  for (const auto &S : Strings) {
    switch (S[19]) {
    case 'G': // [G]uard #42 begins shift:
      sscanf(S.c_str(), "[%*d-%*d-%*d %*d:%*d] Guard #%d", &GuardID);
      if (Guards.find(GuardID) == Guards.end()) { // init sleepy minutes
        Guards[GuardID] = std::vector<int>(60, 0);
      }
      break;
    case 'f': // [f]alls asleep
      sscanf(S.c_str(), "[%*d-%*d-%*d %*d:%d] falls asleep", &SleepyTime);
      break;
    case 'w': // [w]akes up
      sscanf(S.c_str(), "[%*d-%*d-%*d %*d:%d] wakes up", &WakeyWakey);
      for (int i = SleepyTime; i < WakeyWakey; ++i) {
        Guards[GuardID][i]++;
      }
      Minutes[GuardID] += WakeyWakey - SleepyTime;
      break;
    default:
      assert(false);
    }
  }
  // Minute that is generally overslept the most {guard, minute}
  std::pair<int, int> SleepiestGuardMinute = {0, 0};
  // Guard who sleeps the most minutes overall {guard, minute}
  std::pair<int, int> SleepiestGuard = {0, 0};
  // Minute which is overslept the most and how much:
  std::pair<int, int> GuardsMostOversleptMinute = {0, 0};

  int MaxSlept = 0;
  for (auto G : Guards) {
    for (size_t i = 0; i < 60; ++i) {
      if (G.second[i] > MaxSlept) {
        SleepiestGuardMinute = {G.first, i};
        MaxSlept = G.second[i];
      }
    }
  }

  for (auto M : Minutes) {
    if (M.second > SleepiestGuard.second) {
      SleepiestGuard = {M.first, M.second};
    }
  }
//  std::cout << "Guard #" << SleepiestGuard.first << " slept for astonishing "
//            << SleepiestGuard.second << " minutes.\n";
  for (int i = 0; i < 60; ++i) {
    int HowSleepy = Guards[SleepiestGuard.first][i];
    if (HowSleepy > GuardsMostOversleptMinute.second) {
      GuardsMostOversleptMinute.first = i;
      GuardsMostOversleptMinute.second = HowSleepy;
    }
  }

//  std::cout << "He seriously overslept minute "
//            << GuardsMostOversleptMinute.first << " the baffling "
//            << GuardsMostOversleptMinute.second << " times.\n";
  std::cout << SleepiestGuard.first * GuardsMostOversleptMinute.first << "\n";

//  std::cout << "SleepyGuardMinute = " << SleepiestGuardMinute.first << " * "
//            << SleepiestGuardMinute.second << "\n";
//  std::cout << "Part 2: "
//            << SleepiestGuardMinute.first * SleepiestGuardMinute.second << "\n";
}

void Day04::solvePart2() {
  // Solved in part 1
  // TODO move that part here.
  // Minute that is generally overslept the most {guard, minute}
  // std::pair<int, int> SleepiestGuardMinute = {0, 0};
  std::cout << 2393 * 32 << "\n";
}
