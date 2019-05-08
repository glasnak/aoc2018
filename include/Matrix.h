#pragma once

template <typename T> struct Matrix {
  unsigned Rows;
  unsigned Columns;
  std::vector<std::vector<T>> M;

  Matrix() : Rows(0), Columns(0) {}
  Matrix(const unsigned &R, const unsigned &C) : Rows(R), Columns(C) {
    M.reserve(R);
  }

  /// init matrix with default values
  void fill(T BaseItem) {
    M.clear();
    for (unsigned i = 0; i < Rows; ++i) {
      M.emplace_back(std::vector<T>(Columns, BaseItem));
    }
  }

  /// insert an item. Return the item that was on the position before.
  T insert(T Item, Coord Pos) {
    assert(isInRange(Pos));
    T TmpItem = M[Pos.x][Pos.y];
    M[Pos.x][Pos.y] = Item;
    return TmpItem;
  }
  /// Alternative signature for insert
  T insert(T Item, unsigned x, unsigned y) { return insert(Item, Coord(x, y)); }

  /// check if cell position fits the matrix
  bool isInRange(Coord Cell) const {
    return Cell.x >= 0 && Cell.x < (int) Rows && Cell.y >= 0 && Cell.y < (int) Columns;
  }

  /// get the underlying structure
  std::vector<std::vector<T>> get() const { return M; }

  /// return the underlying value on position \Cell.
  T getValue(Coord Cell) const { return M[Cell.x][Cell.y]; }

  std::vector<T> getNeighboursOf(Coord Pos) const {
    assert(isInRange(Pos));
    std::vector<T> Nbors;
    std::vector<Direction> Dirs = {NORTH, WEST, EAST, SOUTH};
    for (const auto Dir : Dirs) {
      Coord NewPos = Coord(Pos.x + Move[Dir].first, Pos.y + Move[Dir].second);
      if (isInRange(NewPos)) {
        Nbors.emplace_back(getValue(NewPos));
      }
    }
    return Nbors;
  }
  
  std::vector<T> getExtendedNeighboursOf(Coord Pos) const {
    std::vector<T> Nbors = getNeighboursOf(Pos);  // 4 Nbors;
    for (const auto VerticalDir : std::vector<Direction>({NORTH, SOUTH})) {
      for (const auto HorizontalDir : std::vector<Direction>({WEST, EAST})) {
        Coord NewPos = Coord(Pos.x + Move[VerticalDir].first, Pos.y + Move[HorizontalDir].second);
        if (isInRange(NewPos)) {
          Nbors.emplace_back(getValue(NewPos));
        }
      }
    }
    return Nbors;
  }

  // return the coord of the max element
  Coord findMaxElement(T &MaxElem) const {
    MaxElem = std::numeric_limits<T>::min();
    Coord MaxElemPos;
    for (unsigned i = 0; i < Rows; ++i) {
      for (unsigned j = 0; j < Columns; ++j) {
        T Value = M[i][j];
        if (MaxElem < Value) {
          MaxElem = Value;
          MaxElemPos = Coord(i, j);
        }
      }
    }
    return MaxElemPos;
  }
  
  unsigned count(T Elem) const {
    unsigned cnt = 0;
    for (unsigned i = 0; i < Rows; ++i) {
      cnt += std::count(M[i].begin(), M[i].end(), Elem);
    }
    return cnt;
  }

  /// print the matrix itself for debug purposes
  void dump(const std::string &Delimiter = ", ") const {
    std::cout << "Matrix of size " << Rows << "x" << Columns << ":\n";
    if (M.empty()) {
      std::cout << "Matrix empty.\n";
      return;
    }
    for (unsigned i = 0; i < Rows; ++i) {
      for (unsigned j = 0; j < Columns; ++j) {
        std::cout << M[i][j] << Delimiter;
      }
      std::cout << "\n";
    }
  }
};
