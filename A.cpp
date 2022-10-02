#include <iostream>

#include <vector>

void Merge(std::vector<long long>& vec, long long left, long long mid,
           long long right) {
  std::vector<long long> merge_vector;
  long long i = left;
  long long j = mid + 1;
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
  for (long long t = left; t <= right; ++t) {
    vec[t] = merge_vector[t - left];
  }
}

void MergeSort(std::vector<long long>& vec, long long left, long long right) {
  if (left < right) {
    long long mid = (right + left) / 2;
    MergeSort(vec, left, mid);
    MergeSort(vec, mid + 1, right);
    Merge(vec, left, mid, right);
  }
}

int main() {
  long long n, k, start0, start1;
  std::cin >> n >> k >> start0 >> start1;
  std::vector<long long> vec;
  vec.push_back(start0);
  vec.push_back(start1);
  long long temp_1 = (long long)vec[0];
  long long temp_2 = (long long)vec[1];
  long long curr;
  for (long long i = 2; i < n; i++) {
    curr = (temp_2 * 123 + temp_1 * 45) % (10000000 + 4321);
    if ((long long)vec.size() < k) {
      vec.push_back(curr);
    } else {
      if (curr < vec[k - 1]) {
        vec[k - 1] = curr;
        MergeSort(vec, 0, k);
      }
    }
    temp_1 = temp_2;
    temp_2 = curr;
  }
  std::cout << vec[k - 1];
}