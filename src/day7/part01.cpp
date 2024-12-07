#include "aoc2024/sol.hpp"

struct equation {
  ll sol{};
  vector<ll> vals{};
  bool is_valid(ll curr, size_t idx) {
    if (idx >= vals.size()) {
      return curr == sol;
    }
    if (is_valid(curr + vals[idx], idx + 1)) {
      return true;
    }
    if (is_valid(curr * vals[idx], idx + 1)) {
      return true;
    }
    return false;
  }
};

equation parse_equation(const string &s) {
  auto idx = s.find(':');
  equation ret;
  ret.sol = stoll(s.substr(0, idx));
  idx += 2;
  while (true) {
    auto nidx = s.find(' ', idx);
    if (nidx == string::npos) {
      nidx = s.size();
    }
    ret.vals.push_back(stoll(s.substr(idx, nidx - idx)));
    if (nidx == s.size())
      break;
    idx = nidx + 1;
  }
  return ret;
}

SOLUTION {
  string line;
  ll ret = 0;
  while (getline(cin, line)) {
    if (line == "")
      break;
    auto eq = parse_equation(line);
    if (eq.is_valid(eq.vals[0], 1)) {
      ret += eq.sol;
    }
  }
  cout << ret << '\n';
}
