#include "aoc2024/sol.hpp"

SOLUTION {
  vector<string> nums;
  string elem;
  while (cin >> elem) {
    nums.push_back(elem);
  }
  auto upd = [](const string &s) -> vector<string> {
    if (s == "0")
      return {"1"};
    if (s.size() % 2 == 0) {
      return {to_string(stoll(s.substr(0, s.size() / 2))),
              to_string(stoll(s.substr(s.size() / 2, s.size() / 2)))};
    }
    return {to_string(stoll(s) * 2024)};
  };
  for (int iter = 0; iter < 25; iter++) {
    vector<string> nxt;
    for (const auto &elem : nums) {
      auto tmp = upd(elem);
      nxt.insert(nxt.end(), tmp.begin(), tmp.end());
    }
    nums.swap(nxt);
  }
  cout << nums.size() << '\n';
}
