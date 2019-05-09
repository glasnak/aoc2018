// --- Day 21: Chronal Conversion ---

#include "Day21.h"

//#include <chrono>

/// originally an assembly program that was manually rewritten to C to utilize compiler opt lol.
static int code(int a) {
  // part 1 - halt as soon as possible:
  // long a = 13270004;
  // part 2 - loop as long as possible:
  // long a = 12879142;
  long b = 0;
  long c = 0;
  long d = 0;
  long e = 0;

  c = 123;
  L1:
  c &= 456;
  c = (c == 72);
  if (c)
    goto L5;
  goto L1;
  L5:
  c = 0;
  L6:
  e = c | 65536;
  c = 15028787;
  L8:
  b = e & 255;
  c += b;
  c &= 16777215;
  c *= 65899;
  c &= 16777215;
  b = (256 > e);
  if (b)
    goto L16;
  goto L17;
  L16:
  goto L28;
  L17:
  b = 0;
  L18:
  d = (b + 1) * 256;
  d = (d > e);
  if (d)
    goto L23;
  goto L24;
  L23:
  goto L26;
  L24:
  b++;
  goto L18;
  L26:
  e = b;
  goto L8;
  L28:
//  printf("%ld\n", c);
  b = (c == a);
  if (b) {
    return d;
  }
  goto L6;
}



/// Another day that involved more debugging than actual coding.
/// Rewrite the assembly into C-with-gotos for simplicity, let your compiler do the optimization instead of doing it manually.
/// Then, simply add printf next to a single usage of a, where the program ends.
/// print the first number, get part 1.
/// wait for the loop, get the last number of the iteration, you get part 2.
void Day21::solvePart1() {
  int Part1 = 13270004;
//  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  code(Part1);
//  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
//  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
//  std::cout << duration << "\n";
  std::cout << Part1 << "\n";
}

/// Part2 is like 1.3M times slower, measured by chrono. Note that for 
/// measurement, the result needs to be assigned to something, otherwise 
/// compiler just optimizes it away as useless.
void Day21::solvePart2() {
  int Part2 = 12879142;
//  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  code(Part2);
//  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
//  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
//  std::cout << duration << "\n";
  std::cout << Part2 << "\n";
}

