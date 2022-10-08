#include <iostream>

bool BinarySearch(const int* begin, const int* end, int target) {
  bool flag = false;
  if (*begin == target or *end == target) {
    flag = true;
  } else if (*end < target or target < *begin) {
    flag = false;
  } else {
    int l = end - begin + 1;
    for (int i = 0; i < l; i++) {
      if (*(begin + (end - begin + 1) / 2) < target) {
        begin += (end - begin + 1) / 2;
      } else if (*(begin + (end - begin + 1) / 2) > target) {
        end -= (end - begin + 1) / 2;
      } else {
        return true;
      }
    }
  }
  return flag;
}

int main() {
  int* num = new int;
  std::cin >> *num;
  int* arr = new int[*num];
  for (int i = 0; i < *num; ++i) {
    std::cin >> arr[i];
  }
  int* begin = new int;
  int* end = new int;
  int* iter_num = new int;
  int target;
  std::cin >> *iter_num;
  for (int i = 0; i < *iter_num; i++) {
    std::cin >> *begin >> *end >> target;
    if (BinarySearch(&arr[*begin], &arr[*end - 1], target)) {
      std::cout << "YES" << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }
  delete[] arr;
  delete num;
  delete iter_num;
  delete begin;
  delete end;
}