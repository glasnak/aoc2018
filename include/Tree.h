#pragma once

template <typename T> class Tree {
private:
  T Value;
  std::vector<T> Metadata;
  std::vector<Tree<T>> Children;

public:
  Tree() = default;
  explicit Tree(T Value) : Value(Value) {}

  void clear() {
    Value = 0;
    Metadata.clear();
    Children.clear();
  }

  void construct(std::deque<T> &Vec) {
    clear();
    if (Vec.size() < 2)
      return;
    // Header
    T NumKids = Vec.front();
    Vec.pop_front();
    T NumMetadata = Vec.front();
    Vec.pop_front();
    // Children.
    for (T i = 0; i < NumKids; ++i) {
      Tree<T> ChildTree;
      ChildTree.construct(Vec);
      Children.push_back(ChildTree);
    }
    // Metadata
    for (T i = 0; i < NumMetadata; ++i) {
      Metadata.push_back(Vec.front());
      Vec.pop_front();
    }
    // Value
    Value = std::accumulate(Metadata.begin(), Metadata.end(), 0);
  }

  // Day08::Part01
  T sum() {
    T SumKids = 0;
    for (auto Child : Children) {
      SumKids += Child.sum();
    }
    return Value + SumKids;
  }

  // Day08::Part02
  T calculateValue() {
    if (Children.empty()) {
      return Value;
    }
    T SumChildren = 0;
    size_t NumChildren = Children.size();
    for (auto Meta : Metadata) { // 1 means Children[0], so:
      if (Meta <= (int)NumChildren) {
        SumChildren += Children[Meta - 1].calculateValue();
      }
    }
    return SumChildren;
  }
};
