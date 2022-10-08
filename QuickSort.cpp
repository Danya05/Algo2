#include <iostream>

#include <vector>

long long Partition(std::vector<long long>& vec, long long left, long long right) {
  long long pivot = vec[(left + right) / 2];
  long long i = left;
  long long j = right;
  while (i <= j) {
    while (vec[i] < pivot) {
      ++i;
    }
    while (vec[j] > pivot) {
      --j;
    }
    if (i >= j) {
      break;
    }
    std::swap(vec[i], vec[j]);
    ++i;
    --j;
  }
  return j;
}

void sub_sort(std::vector<long long>& vec, long long n, long long dist) {
  long long t = n;
  bool not_sorted = true;
  for (long long i = 0; i < n and not_sorted; i += dist) {
    not_sorted = false;
    for (long long j = dist; j < t; j += dist) {
      if (vec[j - dist] > vec[j]) {
        std::swap(vec[j - dist], vec[j]);
        not_sorted = true;
      }
    }
    t -= dist;
  }
}

void Qsort(std::vector<long long>& vec, long long left, long long right) {
  if (left >= right) {
    return;
  }
  long long p = Partition(vec, left, right);
  Qsort(vec, left, p);
  Qsort(vec, p + 1, right);
}

long long Kstat(std::vector<long long>& vec, long long k) {
  long long left = 1;
  long long right = (long long)vec.size();
  while (true) {
    long long mid = Partition(vec, left, right);
    if (mid == k) {
      return mid;
    }
    if (mid < k) {
      left = mid + 1;
    }
    if (mid > k) {
      right = mid;
    }
  }
}
int main() {
  long long n;
  std::cin >> n;
  std::vector<long long> vec(n);
  for (long long i = 0; i < n; ++i) {
    std::cin >> vec[i];
  }
  Qsort(vec, 0, n - 1);
  for (long long i = 0; i < n; ++i) {
    std::cout << vec[i] << " ";
  }
}
