#include <iostream>

#include <vector>

void merge(std::vector<int> vec, int left, int mid, int right);

void merge_sort(std::vector<int> vec, int left, int right) {
  int mid;
  if (left < right) {
    mid = (right + left) / 2;
    merge_sort(vec, left, mid);
    merge_sort(vec, mid + 1, right);
    merge(vec, left, mid, right);
  }
}

void merge(std::vector<int> vec, int left, int mid, int right) {
  std::vector<int> vec1(vec.begin() + left, vec.begin() + mid);
  std::vector<int> vec2(vec.begin() + mid, vec.begin() + right);
  int i, j;
  for(i = 0, j = 0; i < mid - left and j < right - mid; ++i, ++j) {
    if (vec1[i] < vec2[j]) {
      vec[left++] = vec1[i];
    } else {
      vec[left++] = vec2[i];
    }
  }
  while (i < vec1.size()) {
    vec[left++] = vec1[i++];
  }
  while (j < vec2.size()) {
    vec[left++] = vec2[j++];
  }
}

int main() {
  int N;
  std::cin >> N;
  std::vector<int> vec(2*N);
  for (int i = 0; i < 2*N; i += 2) {
    std::cin >> vec[i] >> vec[i + 1];
  }
  merge_sort(vec, 0, 2*N - 1);
  for (int i = 0; i < 2*N; i += 2) {
    std::cout << vec[i] << "\t" << vec[i + 1] << '\n';
  }
}