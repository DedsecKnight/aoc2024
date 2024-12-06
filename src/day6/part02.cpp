#include "aoc2024/sol.hpp"

constexpr const array<int, 4> dx{-1, 0, 1, 0};
constexpr const array<int, 4> dy{0, 1, 0, -1};

bool check_cycle(const vector<string> &grid) {
  auto n = grid.size(), m = grid[0].size();
  queue<pair<size_t, int>> q;
  vector<vector<bool>> visited(n * m, vector<bool>(4, false));
  for (auto i = 0; i < n; i++) {
    for (auto j = 0; j < m; j++) {
      if (grid[i][j] == '^') {
        q.emplace(i * m + j, 0);
        visited[i * m + j][0] = true;
      }
    }
  }
  while (!q.empty()) {
    auto [curr, dir] = q.front();
    q.pop();
    auto i = curr / m, j = curr % m;
    size_t nx, ny;
    bool finished = false;
    int iter = 0;
    while (true) {
      nx = i + dx[dir], ny = j + dy[dir];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
        return false;
      }
      if (grid[nx][ny] == '#') {
        dir = (dir + 1) % 4;
        continue;
      }
      break;
    }
    if (finished)
      break;
    if (!visited[nx * m + ny][dir]) {
      visited[nx * m + ny][dir] = true;
      q.emplace(nx * m + ny, dir);
    } else {
      return true;
    }
  }
  return false;
}

SOLUTION {
  vector<string> grid;
  string line;
  while (getline(cin, line)) {
    if (line == "")
      break;
    grid.push_back(line);
  }
  auto n = grid.size(), m = grid[0].size();
  int ret = 0;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      if (grid[i][j] == '.') {
        grid[i][j] = '#';
        ret += check_cycle(grid);
        grid[i][j] = '.';
      }
    }
    cout << "done row " << i << '\n';
  }
  cout << ret << '\n';
}
