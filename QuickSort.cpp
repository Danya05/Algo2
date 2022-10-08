#include <iostream>

#include <vector>

long long Partition(std::vector<long long>& vec, long long left,
                    long long right) {
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

void Qsort(std::vector<long long>& vec, long long left, long long right) {
  if (left >= right) {
    return;
  }
  long long p = Partition(vec, left, right);
  Qsort(vec, left, p);
  Qsort(vec, p + 1, right);
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
