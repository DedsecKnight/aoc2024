#include "aoc2024/sol.hpp"

bool is_valid(const vector<int> &a) {
  if (a.empty())
    return false;
  bool inc = false, dec = false;
  for (size_t i = 1; i < a.size(); i++) {
    if (a[i] > a[i - 1])
      inc = true;
    else if (a[i] < a[i - 1])
      dec = true;
    else
      return false;
  }
  if (inc && dec)
    return false;
  for (size_t i = 1; i < a.size(); i++) {
    if (abs(a[i] - a[i - 1]) > 3)
      return false;
  }
  return true;
}

vector<int> parse_line(const string &s) {
  int curr = 0;
  vector<int> ret;
  if (s == "")
    return ret;
  for (char c : s) {
    if (isdigit(c))
      curr = curr * 10 + (c - '0');
    else {
      ret.push_back(curr);
      curr = 0;
    }
  }
  ret.push_back(curr);
  return ret;
}

SOLUTION {
  string line;
  int cnt = 0;
  while (getline(cin, line)) {
    auto a = parse_line(line);
    bool valid = is_valid(a);
    for (size_t i = 0; i < a.size() && !valid; i++) {
      vector<int> ca(a.begin(), a.end());
      ca.erase(ca.begin() + i);
      if (is_valid(ca)) {
        valid = true;
        break;
      }
    }
    cnt += valid;
  }
  cout << cnt << '\n';
}
