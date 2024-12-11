#include "aoc2024/sol.hpp"

SOLUTION {
  vector<string> nums;
  string elem;
  while (cin >> elem) {
    nums.push_back(elem);
  }
  map<pair<string, int>, ll> memo;
  function<ll(string, int)> solve = [&](string s, int step) {
    auto k = make_pair(s, step);
    if (memo.find(k) != memo.end())
      return memo[k];
    if (step == 0)
      return memo[k] = 1;
    if (s == "0") {
      return memo[k] = solve("1", step - 1);
    }
    if (s.size() % 2 == 0) {
      auto left = to_string(stoll(s.substr(0, s.size() / 2)));
      auto right = to_string(stoll(s.substr(s.size() / 2, s.size() / 2)));
      return memo[k] = solve(left, step - 1) + solve(right, step - 1);
    }
    return memo[k] = solve(to_string(stoll(s) * 2024), step - 1);
  };
  ll ret =
      accumulate(nums.begin(), nums.end(), 0ll,
                 [&](auto acc, const auto &s) { return acc + solve(s, 75); });
  cout << ret << '\n';
}
