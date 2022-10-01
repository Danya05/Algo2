#include <iostream>

#include <vector>

void merge(std::vector<int>* vec, int n, int mid, int m);

void merge_sort(std::vector<int> vec, int left, int right) {
  int n = right - left;
  int mid = left + (right - left) / 2;
  if (n > 1) {
    merge_sort(vec,left, mid);
    merge_sort(vec, mid, right);
    std::vector<int> vec1(vec.begin()+left, vec.begin()+mid);
    std::vector<int> vec2(vec.begin()+mid, vec.begin() + right);
    int i = left;
    int j = mid;
    while (i < mid and j < right) {
      if (vec1[i] < vec2[j]) {
        vec[i + j] = vec1[i];
        ++i;
      } else {
        vec[i + j] = vec1[i];
        ++j;
      }
    }
    while (i < mid) {
      vec[i + j] = vec1[i];
      ++i;
    }
    while (j < right) {
      vec[i + j] = vec1[i];
      ++j;
    }
  }
}

int main() {
  int N;
  std::cin >> N;
  std::vector<int> vec(N);
  for (int i = 0; i < 2*N; i += 2) {
    int a;
    int b;
    std::cin >> a >> b;
    if (!vec.empty()){
      for (int j = 0; j < vec.size(); ++j) {
        if (a <= vec[j]) {

        }
      }
    }
    vec[i] = a;
    vec[i + 1] = b;
  }
}