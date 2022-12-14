#include <iostream>
#include <vector>

std::vector<int> tree;

void Merge(std::vector<std::pair<int, int>>& a, int l, int r) {
  int mid = l + (r - l) / 2;
  int i = 0;
  int j = 0;
  std::vector<std::pair<int, int>> res(r - l);
  while (l + i < mid and mid + j < r) {
    if (a[l + i].first < a[mid + j].first or
        (a[l + i].first == a[mid + j].first and
         a[l + i].second > a[mid + j].second)) {
      res[i + j] = a[l + i];
      i++;
    } else {
      res[i + j] = a[mid + j];
      j++;
    }
  }
  while (l + i < mid) {
    res[i + j] = a[l + i];
    i++;
  }
  while (mid + j < r) {
    res[i + j] = a[mid + j];
    j++;
  }
  for (int z = 0; z < r - l; z++) {
    a[l + z] = res[z];
  }
}

void MergeSort(std::vector<std::pair<int, int>>& a, int l, int r) {
  if (l + 1 >= r) {
    return;
  }
  int mid = l + (r - l) / 2;
  MergeSort(a, l, mid);
  MergeSort(a, mid, r);
  Merge(a, l, r);
}

void ReadVec(std::vector<std::pair<int, int>>& a) {
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i].first;
    a[i].second = static_cast<int>(i);
  }
}

void Build(int v, int l, int r, int idx, int value) {
  if (idx < l or idx > r) {
    return;
  }
  if (l == r) {
    tree[v] = value;
    return;
  }
  int mid = l + (r - l) / 2;
  Build(2 * v + 1, l, mid, idx, value);
  Build(2 * v + 2, mid + 1, r, idx, value);
  tree[v] = std::max(tree[2 * v + 1], tree[2 * v + 2]);
}

int RmqTree(int v, int tl, int tr, int l, int r) {
  if (l <= tl and r >= tr) {
    return tree[v];
  }
  if (r < tl or l > tr) {
    return 0;
  }
  int mid = (tl + tr) / 2;
  return std::max(RmqTree(2 * v + 1, tl, mid, l, r),
                  RmqTree(2 * v + 2, mid + 1, tr, l, r));
}

int main() {
  int num;
  std::cin >> num;
  std::vector<std::pair<int, int>> vec(num);
  ReadVec(vec);
  MergeSort(vec, 0, num);
  tree.assign(4 * num, 0);
  for (size_t i = 0; i < static_cast<size_t>(num); ++i) {
    Build(0, 0, num - 1, vec[i].second,
          RmqTree(0, 0, num - 1, 0, vec[i].second) + 1);
  }
  std::cout << tree[0];
}
