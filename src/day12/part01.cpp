#include "aoc2024/sol.hpp"

constexpr const array<int, 4> dx{-1, 1, 0, 0};
constexpr const array<int, 4> dy{0, 0, -1, 1};

SOLUTION {
  vector<string> grid;
  string line;
  while (cin >> line) {
    grid.push_back(line);
  }
  int n = int(grid.size()), m = int(grid[0].size());
  vector<vector<bool>> visited(n, vector<bool>(m));
  int area = 0, perimeter = 0;
  int ret = 0;
  function<void(int, int)> dfs = [&](int i, int j) {
    visited[i][j] = true;
    area++;
    for (int k = 0; k < 4; k++) {
      int nx = i + dx[k], ny = j + dy[k];
      if (nx < 0 || ny < 0 || nx >= n || ny >= m ||
          grid[nx][ny] != grid[i][j]) {
        perimeter++;
      } else if (!visited[nx][ny]) {
        dfs(nx, ny);
      }
    }
  };
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!visited[i][j]) {
        dfs(i, j);
        ret += area * perimeter;
        area = perimeter = 0;
      }
    }
  }
  cout << ret << '\n';
}
