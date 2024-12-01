#include "aoc2024/sol.hpp"

namespace aoc2024 {
void solution::solve() const noexcept {
  vector<int> ls;
  unordered_map<int, int> cnt;
  int x, y;
  while (cin >> x >> y) {
    cnt[y]++;
    ls.push_back(x);
  }
  ll ret = 0;
  for (auto elem : ls) {
    ret += elem * 1ll * cnt[elem];
  }
  cout << ret << '\n';
}
} // namespace aoc2024
