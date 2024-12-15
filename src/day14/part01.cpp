#include "aoc2024/sol.hpp"

pair<int, int> parse_vector(const string &s) {
  auto eidx = s.find('=');
  auto cidx = s.find(',');
  return make_pair(stoi(s.substr(cidx + 1, s.size() - cidx - 1)),
                   stoi(s.substr(eidx + 1, cidx - eidx - 1)));
}

SOLUTION {
  vector<pair<int, int>> pos, velocity;
  string buf;
  while (cin >> buf) {
    pos.push_back(parse_vector(buf));
    cin >> buf;
    velocity.push_back(parse_vector(buf));
  }
  int n = 103, m = 101, sz = int(pos.size());
  for (int iter = 0; iter < 100; iter++) {
    vector<pair<int, int>> nxt_pos;
    for (int i = 0; i < sz; i++) {
      auto nx = pos[i].first + velocity[i].first,
           ny = pos[i].second + velocity[i].second;
      nxt_pos.emplace_back((nx + n) % n, (ny + m) % m);
    }
    pos.swap(nxt_pos);
  }
  vector<int> cnt(4);
  for (auto [x, y] : pos) {
    if (x < n / 2) {
      if (y < m / 2) {
        cnt[0]++;
      } else if (y > m / 2) {
        cnt[1]++;
      }
    } else if (x > n / 2) {
      if (y < m / 2) {
        cnt[2]++;
      } else if (y > m / 2) {
        cnt[3]++;
      }
    }
  }
  cout << cnt[0] * cnt[1] * cnt[2] * cnt[3] << '\n';
}
