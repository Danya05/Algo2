#include <iostream>
#include <vector>

void Display(const std::vector<std::vector<std::pair<int, int>>>& prev,
             const std::vector<int>& a, int i, int j) {
  if (i == 0 or j == 0) {
    return;
  }
  if (prev[i][j] == std::make_pair(i - 1, j - 1)) {
    Display(prev, a, i - 1, j - 1);
    std::cout << a[i] << ' ';
  } else {
    if (prev[i][j] == std::make_pair(i - 1, j)) {
      Display(prev, a, i - 1, j);
    } else {
      Display(prev, a, i, j - 1);
    }
  }
}

int main() {
  int num1;
  std::cin >> num1;
  std::vector<int> a(num1);
  for (size_t i = 0; i < static_cast<size_t>(num1); ++i) {
    std::cin >> a[i];
  }
  int num2;
  std::cin >> num2;
  std::vector<int> b(num2);
  for (size_t i = 0; i < static_cast<size_t>(num2); ++i) {
    std::cin >> b[i];
  }
  a.insert(a.begin(), 0);
  b.insert(b.begin(), 0);
  std::vector<std::vector<int>> dp(num1 + 1, std::vector<int>(num2 + 1, 0));
  std::vector<std::vector<std::pair<int, int>>> prev(
      num1 + 1, std::vector<std::pair<int, int>>(num2 + 1, {0, 0}));
  for (int i = 1; i <= num1; ++i) {
    for (int j = 1; j <= num2; ++j) {
      if (a[i] == b[j]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        prev[i][j] = std::make_pair(i - 1, j - 1);
      } else if (dp[i - 1][j] >= dp[i][j - 1]) {
        dp[i][j] = dp[i - 1][j];
        prev[i][j] = std::make_pair(i - 1, j);
      } else {
        dp[i][j] = dp[i][j - 1];
        prev[i][j] = std::make_pair(i, j - 1);
      }
    }
  }
  Display(prev, a, num1, num2);
}
