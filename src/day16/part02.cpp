#include "aoc2024/sol.hpp"

constexpr const array<int, 4> dx{0, 1, 0, -1};
constexpr const array<int, 4> dy{1, 0, -1, 0};

vector<int> calc_dist(const vector<string> &grid, pair<int, int> src) {
  int n = int(grid.size()), m = int(grid[0].size());
  vector<int> dist(n * m * 4, 1e9 + 10);
  deque<pair<int, int>> q;
  dist[src.first * 4 + src.second] = 0;
  q.emplace_back(src.first, src.second);
  while (!q.empty()) {
    auto [pos, dir] = q.front();
    q.pop_front();
    int i = pos / m, j = pos % m;
    int nx = i + dx[dir], ny = j + dy[dir];
    int np = nx * m + ny;
    if (nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] != '#' &&
        dist[np * 4 + dir] > dist[pos * 4 + dir] + 1) {
      dist[np * 4 + dir] = dist[pos * 4 + dir] + 1;
      q.emplace_front(np, dir);
    }
    int nd = (dir + 1) % 4;
    if (dist[pos * 4 + nd] > dist[pos * 4 + dir] + 1000) {
      dist[pos * 4 + nd] = dist[pos * 4 + dir] + 1000;
      q.emplace_back(pos, nd);
    }
    nd = (dir + 3) % 4;
    if (dist[pos * 4 + nd] > dist[pos * 4 + dir] + 1000) {
      dist[pos * 4 + nd] = dist[pos * 4 + dir] + 1000;
      q.emplace_back(pos, nd);
    }
  }
  return dist;
}

SOLUTION {
  string line;
  vector<string> grid;
  while (getline(cin, line)) {
    grid.push_back(line);
  }
  int n = int(grid.size()), m = int(grid[0].size());
  vector<int> ds;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 'S') {
        ds = calc_dist(grid, make_pair(i * m + j, 0));
        break;
      }
    }
  }
  int best = 1e9 + 10, dest;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 'E') {
        dest = i * m + j;
        for (int k = 0; k < 4; k++) {
          best = min(best, ds[(i * m + j) * 4 + k]);
        }
      }
    }
  }
  vector<vector<bool>> marked(n, vector<bool>(m));
  for (int k = 0; k < 4; k++) {
    if (ds[dest * 4 + k] == best) {
      auto de = calc_dist(grid, make_pair(dest, (k + 2) % 4));
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          int pos = i * m + j;
          for (int k2 = 0; k2 < 4; k2++) {
            if (ds[pos * 4 + k2] + de[pos * 4 + (k2 + 2) % 4] == best) {
              marked[i][j] = true;
            }
          }
        }
      }
    }
  }
  int ret = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ret += marked[i][j];
    }
  }
  cout << ret << '\n';
}
