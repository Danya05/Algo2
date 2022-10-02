#include <iostream>

#include <vector>

void merge(std::vector<int>& vec, int left, int mid, int right) {
  std::vector<int> merge_vector;
  int i = left;
  int j = mid + 1;
  while (i <= mid and j <= right) {
    if (vec[i] <= vec[j]) {
      merge_vector.push_back(vec[i++]);
    } else {
      merge_vector.push_back(vec[j++]);
    }
  }
  while (i <= mid) {
    merge_vector.push_back(vec[i++]);
  }
  while (j <= right) {
    merge_vector.push_back(vec[j++]);
  }
  for (int t = left; t <= right; ++t) {
    vec[t] = merge_vector[t-left];
  }
}

void merge_sort(std::vector<int>& vec, int left, int right) {
  if (left < right) {
    int mid = (right + left) / 2;
    merge_sort(vec, left, mid);
    merge_sort(vec, mid + 1, right);
    merge(vec, left, mid, right);
  }
}

int main() {
  int N;
  std::cin >> N;
  std::vector<int> vec1(N);
  std::vector<int> vec2(N);
  std::vector<int> res;
  for (int i = 0; i < N; i++) {
    std::cin >> vec1[i] >> vec2[i];
  }
  merge_sort(vec1, 0, N);
  merge_sort(vec2, 0, N);
  
}