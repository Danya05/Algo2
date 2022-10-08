#include <iostream>

#include <vector>

long long GetDigit(long long num, size_t index) {
  return num >> (8 * index) & 255;
}

void LsdSort(std::vector<long long>& vec) {
  size_t size = sizeof(long long);
  for (size_t iter = 0; iter < size; ++iter) {
    std::vector<long long> res(vec.size());
    std::vector<size_t> curr(256, 0);
    for (size_t j = 0; j < vec.size(); ++j) {
      curr[GetDigit(vec[j], iter)] += 1;
    }
    for (size_t j = 1; j < 256; ++j) {
      curr[j] += curr[j - 1];
    }
    for (size_t j = vec.size() - 1; true; --j) {
      res[--curr[GetDigit(vec[j], iter)]] = vec[j];
      if (j == 0) {
        break;
      }
    }

    for (size_t j = 0; j < vec.size(); ++j) {
      vec[j] = res[j];
    }
  }
}

int main() {
  size_t n;
  std::cin >> n;
  std::vector<long long> vec(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> vec[i];
  }
  LsdSort(vec);
  for (size_t i = 0; i < n; ++i) {
    std::cout << vec[i] << ' ';
  }
}