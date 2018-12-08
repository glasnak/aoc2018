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
    for (unsigned i = 0; i < Rows; ++i) {
      M.emplace_back(std::vector<T>(Columns, BaseItem));
    }
  }

  /// insert an item. Return the item that was on the position before.
  T insert(T Item, Coord Pos) {
    T TmpItem = M[Pos.x][Pos.y];
    M[Pos.x][Pos.y] = Item;
    return TmpItem;
  }
  /// Alternative signature for insert
  T insert(T Item, unsigned x, unsigned y) { return insert(Item, Coord(x, y)); }

  /// check if cell position fits the matrix
  bool isInRange(Coord Cell) {
    return Cell.x >= 0 && Cell.x < Columns && Cell.y >= 0 && Cell.y < Rows;
  }

  /// get the underlying structure
  std::vector<std::vector<T>> get() { return M; }

  /// return the underlying value on position \Cell.
  T getValue(Coord Cell) { return M[Cell.x][Cell.y]; }

  /// print the matrix itself for debug purposes
  void dump() const {
    std::cout << "Matrix of size " << Rows << "x" << Columns << ":\n";
    if (M.empty()) {
      std::cout << "Matrix empty.\n";
      return;
    }
    for (unsigned i = 0; i < Rows; ++i) {
      for (unsigned j = 0; j < Columns; ++j) {
        std::cout << M[i][j] << ",  ";
      }
      std::cout << "\n";
    }
  }
};
