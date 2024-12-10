#include "aoc2024/sol.hpp"

constexpr const array<int, 4> dx{-1, 1, 0, 0};
constexpr const array<int, 4> dy{0, 0, -1, 1};

SOLUTION {
  string line;
  vector<string> grid;
  while (cin >> line) {
    grid.push_back(line);
  }
  int n = int(grid.size()), m = int(grid[0].size());
  vector<pair<int, int>> start;
  vector<vector<int>> dist(n, vector<int>(m, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == '9') {
        start.emplace_back(i, j);
        dist[i][j] = 1;
      }
    }
  }
  for (auto elem : start) {
    queue<pair<int, int>> q;
    q.push(elem);
    vector<vector<bool>> visited(n, vector<bool>(m));
    visited[elem.first][elem.second] = true;
    while (!q.empty()) {
      auto [i, j] = q.front();
      q.pop();
      for (int k = 0; k < 4; k++) {
        int nx = i + dx[k], ny = j + dy[k];
        if (nx < 0 || ny < 0 || nx >= n || ny >= m)
          continue;
        if (grid[nx][ny] == grid[i][j] - 1 && !visited[nx][ny]) {
          visited[nx][ny] = true;
          q.emplace(nx, ny);
        }
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (grid[i][j] == '0')
          dist[i][j] += visited[i][j];
      }
    }
  }
  int ret = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == '0') {
        ret += dist[i][j];
      }
    }
  }
  cout << ret << '\n';
}
