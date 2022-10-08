#include <iostream>

#include <vector>

class BinaryHeap {
 private:
  std::vector<std::pair<long long, long long>> vec_;

 public:
  void SiftUp(long long index_elem);
  void SiftDown(long long index_parent);
  void ExtractMin();
  void DecreaseKey(long long current, long long index, long long delta);
  void Heapify(long long index);
  void Insert(std::pair<long long, long long> item);
  long long GetMin();
};

void BinaryHeap::SiftUp(long long index_elem) {
  if (index_elem > 0) {
    if (vec_[index_elem].first < vec_[(index_elem - 1) / 2].first) {
      std::swap(vec_[index_elem], vec_[(index_elem - 1) / 2]);
      SiftUp((index_elem - 1) / 2);
    }
  }
}

void BinaryHeap::SiftDown(long long index_parent) {
  long long res_idx = index_parent;
  long long index = 2 * index_parent + 1;
  if (index < (long long)vec_.size() and vec_[index] < vec_[res_idx]) {
    res_idx = 2 * index_parent + 1;
  }
  if (index + 1 < (long long)vec_.size() and vec_[index + 1] < vec_[res_idx]) {
    res_idx = 2 * index_parent + 2;
  }
  if (res_idx != index_parent) {
    std::swap(vec_[res_idx], vec_[index_parent]);
    SiftDown(res_idx);
  }
}
void BinaryHeap::ExtractMin() {
  std::swap(vec_[0], vec_[vec_.size() - 1]);
  vec_.pop_back();
  SiftDown(0);
}
void BinaryHeap::Heapify(long long index) {
  long long left = 2 * index + 1;
  long long right = 2 * index + 2;
  long long current = index;
  if (left < (long long)vec_.size() and vec_[left].first < vec_[index].first) {
    current = left;
  }
  if (right < (long long)vec_.size() and
      vec_[right].first < vec_[current].first) {
    current = right;
  }
  if (current != index) {
    std::swap(vec_[index], vec_[current]);
    SiftDown(current);
  }
}

void BinaryHeap::Insert(std::pair<long long, long long> item) {
  vec_.push_back(item);
  SiftUp((long long)vec_.size() - 1);
}
long long BinaryHeap::GetMin() { return vec_[0].first; }
void BinaryHeap::DecreaseKey(long long current, long long index,
                             long long delta) {
  if (vec_[current].second == index) {
    vec_[current].first -= delta;
    SiftUp(current);
    SiftDown(0);
  } else {
    long long left_child = 2 * current + 1;
    long long right_child = 2 * current + 2;
    if (left_child < (long long)vec_.size()) {
      DecreaseKey(left_child, index, delta);
    }
    if (right_child < (long long)vec_.size()) {
      DecreaseKey(right_child, index, delta);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  BinaryHeap x;
  long long n;
  std::cin >> n;
  std::string s;
  for (long long i = 0; i < n; ++i) {
    std::cin >> s;
    if (s == "getMin") {
      std::cout << x.GetMin() << '\n';
    } else if (s == "insert") {
      long long temp;
      std::cin >> temp;
      x.Insert({temp, i + 1});
    } else if (s == "extractMin") {
      x.ExtractMin();
    } else {
      long long index;
      long long delta;
      std::cin >> index >> delta;
      x.DecreaseKey(0, index, delta);
    }
  }
}