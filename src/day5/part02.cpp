#include "aoc2024/sol.hpp"

pair<int, int> parse_rule(const string &s) {
  auto idx = s.find('|');
  return make_pair(stoi(s.substr(0, idx)),
                   stoi(s.substr(idx + 1, s.size() - 1 - idx)));
}

vector<int> parse_query(const string &s) {
  size_t lb = 0;
  vector<int> ret;
  while (lb < s.size()) {
    auto nlb = min(s.find(',', lb), s.size());
    ret.push_back(stoi(s.substr(lb, nlb - lb)));
    lb = nlb + 1;
  }
  return ret;
}

SOLUTION {
  string line;
  vector<pair<int, int>> rules;
  while (getline(cin, line)) {
    if (line == "")
      break;
    auto [f, s] = parse_rule(line);
    rules.emplace_back(f, s);
  }
  int ret = 0;
  while (getline(cin, line)) {
    auto query = parse_query(line);
    int cnt = 0;
    while (true) {
      bool valid = true;
      for (auto [f, s] : rules) {
        auto i1 = find(query.begin(), query.end(), f) - query.begin();
        auto i2 = find(query.begin(), query.end(), s) - query.begin();
        if (i1 == query.size() || i2 == query.size())
          continue;
        if (i1 > i2) {
          valid = false;
          swap(query[i1], query[i2]);
        }
      }
      if (valid)
        break;
      else
        cnt++;
    }
    if (cnt > 0)
      ret += query[query.size() / 2];
  }
  cout << ret << '\n';
}
