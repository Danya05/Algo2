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
  long long n, k, start0, start1;
  std::cin >> n >> k >> start0 >> start1;
  std::vector<long long> vec(n);
  vec[0] = start0;
  vec[1] = start1;
  for (long long i = 2; i < n; i++) {
    vec[i] = (vec[i - 1] * 123 + vec[i - 2] * 45) % (10000000 + 4321);
  }
  std::cout << vec[Kstat(vec, k)];
}
