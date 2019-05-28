#pragma once

#include "Day.h"
#include "Matrix.h"


static const bool TESTING = false;

static const unsigned CAVE_DEPTH = (TESTING) ? 510 : 8103;
static const Coord CAVE_TARGET = (TESTING) ? Coord(10,10) : Coord(758, 9);

static const Coord CAVE_SIZE = Coord(CAVE_TARGET.x + 1000, CAVE_TARGET.y + 1000);


class Day22 : public Day {
  enum RegionType {
    ROCKY = 0,
    WET = 1,
    NARROW = 2,
    INVALID_TYPE = 9999
  };
  
  enum ToolType {
    TORCH = 0,
    GEAR = 1,
    NOTHING = 2,
    INVALID_TOOL = 9999
  };

  struct Region {
    Region(RegionType type, long geoIndex, long eroLevel) : Type(type), GeoIndex(geoIndex), EroLevel(eroLevel) {}
    explicit Region(long geoIndex) : GeoIndex(geoIndex) {
      EroLevel = (geoIndex + CAVE_DEPTH) % 20183;
      Type = static_cast<Day22::RegionType>(EroLevel % 3);
    }
    RegionType Type;
    long GeoIndex;
    long EroLevel;
  };
  
  Matrix<Region> Cave;
  void generate();
  void dumpCave();
  int sumCave();

public:
  Day22() : Day(22) {}
  void solvePart1() override;
  void solvePart2() override;
  ~Day22() override = default;
};
