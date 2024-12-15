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
  for (int iter = 0; iter < 100000; iter++) {
    vector<pair<int, int>> nxt_pos;
    for (int i = 0; i < sz; i++) {
      auto nx = pos[i].first + velocity[i].first,
           ny = pos[i].second + velocity[i].second;
      nxt_pos.emplace_back((nx + n) % n, (ny + m) % m);
    }
    pos.swap(nxt_pos);
    vector<vector<bool>> marked(n, vector<bool>(m));
    for (auto [x, y] : pos) {
      marked[x][y] = true;
    }
    cout << "iter = " << iter << '\n';
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (marked[i][j])
          cout << "X";
        else
          cout << " ";
      }
      cout << '\n';
    }
    cout << '\n' << '\n';
  }
}
