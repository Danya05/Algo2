#include <algorithm>
#include <iostream>
#include <vector>

void Merge(std::vector<std::pair<int, int>>& a, int l, int r) {
  int mid = l + (r - l) / 2;
  int i = 0;
  int j = 0;
  std::vector<std::pair<int, int>> res(r - l);
  while(l + i < mid && mid + j < r) {
    if (a[l+i].first < a[mid + j].first) {
      res[i + j] = a[l + i];
      i++;
    } else {
      res[i + j] = a[mid + j];
      j++;
    }
  }
  while(l + i < mid) {
    res[i + j] = a[l + i];
    i++;
  }
  while(mid + j < r) {
    res[i + j] = a[mid + j];
    j++;
  }
  for (int z = 0; z < r - l; z++){
    a[l + z] = res[z];
  }
}

void MergeSort(std::vector<std::pair<int, int>>& a, int l, int r) {
  if (l + 1 >= r)
    return;
  int mid = l + (r - l) / 2;
  MergeSort(a, l, mid);
  MergeSort(a, mid, r);
  Merge(a, l, r);
}

void ReadVec(std::vector<std::pair<int, int>>& a) {
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i].first;
    a[i].second = static_cast<int>(i) + 1;
  }
}

int main() {
  int num;
  std::cin >> num;
  std::vector<std::pair<int, int>> vec(num);
  ReadVec(vec);
  MergeSort(vec, 0, num);
  std::cout << num;
}
