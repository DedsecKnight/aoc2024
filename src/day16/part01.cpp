#include "aoc2024/sol.hpp"

constexpr const array<int, 4> dx{0, 1, 0, -1};
constexpr const array<int, 4> dy{1, 0, -1, 0};

SOLUTION {
  string line;
  vector<string> grid;
  while (getline(cin, line)) {
    grid.push_back(line);
  }
  int n = int(grid.size()), m = int(grid[0].size());
  vector<int> dist(n * m * 4, 1e9 + 10);
  deque<pair<int, int>> q;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 'S') {
        dist[(i * m + j) * 4] = 0;
        q.emplace_back(i * m + j, 0);
      }
    }
  }
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
  int ret = 1e9 + 10;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 'E') {
        int pos = i * m + j;
        for (int k = 0; k < 4; k++) {
          ret = min(ret, dist[pos * 4 + k]);
        }
      }
    }
  }
  cout << ret << '\n';
}
