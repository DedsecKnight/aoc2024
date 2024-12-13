#include "aoc2024/sol.hpp"

typedef vector<double> vd;
const double eps = 1e-12;

pair<ll, ll> parse_button(const string &line) {
  auto idx = line.find('+');
  auto cidx = line.find(',');
  int p1 = stoi(line.substr(idx + 1, cidx - idx - 1));
  idx = line.find('+', cidx);
  int p2 = stoi(line.substr(idx + 1, line.size() - 1 - idx));
  return make_pair(p1, p2);
}

pair<ll, ll> parse_prize(const string &line) {
  auto idx = line.find('=');
  auto cidx = line.find(',');
  int p1 = stoi(line.substr(idx + 1, cidx - idx - 1));
  idx = line.find('=', cidx);
  int p2 = stoi(line.substr(idx + 1, line.size() - 1 - idx));
  return make_pair(p1 + 10000000000000ll, p2 + 10000000000000ll);
}

SOLUTION {
  string line;
  ll ret = 0;
  while (getline(cin, line)) {
    auto ba = parse_button(line);
    getline(cin, line);
    auto bb = parse_button(line);
    getline(cin, line);
    auto p = parse_prize(line);
    getline(cin, line);
    auto numerator = ba.second * p.first - p.second * ba.first;
    auto denominator = ba.second * bb.first - ba.first * bb.second;
    if (numerator % denominator == 0) {
      auto x2 = numerator / denominator;
      if ((p.first - bb.first * x2) % ba.first)
        continue;
      auto x1 = (p.first - bb.first * x2) / ba.first;
      ret += x1 * 3 + x2;
    }
  }
  cout << ret << '\n';
}
