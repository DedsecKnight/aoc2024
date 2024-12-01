#include "aoc2024/sol.hpp"

namespace aoc2024 {
void solution::solve() const noexcept {
  vector<int> l1, l2;
  int x, y;
  while (cin >> x >> y) {
    l1.push_back(x);
    l2.push_back(y);
  }
  sort(l1.begin(), l1.end());
  sort(l2.begin(), l2.end());
  ll ret = 0;
  for (size_t i = 0; i < l1.size(); i++) {
    ret += abs(l1[i] - l2[i]);
  }
  cout << ret << '\n';
}
} // namespace aoc2024
