#include "aoc2024/sol.hpp"

constexpr const array<int, 4> dx{-1, 0, 1, 0};
constexpr const array<int, 4> dy{0, -1, 0, 1};

constexpr const array<int, 4> ddx{-1, 1, 1, -1};
constexpr const array<int, 4> ddy{-1, -1, 1, 1};

SOLUTION {
  vector<string> grid;
  string line;
  while (cin >> line) {
    grid.push_back(line);
  }
  int n = int(grid.size()), m = int(grid[0].size());
  vector<vector<int>> visited(n, vector<int>(m, -1));
  vector<pair<int, int>> pos;
  int area = 0, perimeter = 0;
  int ret = 0;
  function<void(int, int)> dfs = [&](int i, int j) {
    area++;
    pos.emplace_back(i, j);
    visited[i][j] = 0;
    for (int k = 0; k < 4; k++) {
      int nx = i + dx[k], ny = j + dy[k];
      if (nx < 0 || ny < 0 || nx >= n || ny >= m ||
          grid[nx][ny] != grid[i][j]) {
        visited[i][j] = 1;
      } else if (visited[nx][ny] == -1) {
        dfs(nx, ny);
      }
    }
  };
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (visited[i][j] == -1) {
        dfs(i, j);
        for (auto [x, y] : pos) {
          if (visited[x][y] != 1)
            continue;
          vector<int> d(2);
          for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                grid[nx][ny] == grid[x][y]) {
              d[k % 2] += 1;
            }
          }
          if (d[0] < d[1]) {
            swap(d[0], d[1]);
          }
          if (d[0] == 0) {
            perimeter += 4;
          } else if (d[0] == 1) {
            if (d[1] == 0) {
              perimeter += 2;
            } else {
              perimeter += 1;
            }
          }
        }
        for (auto [x, y] : pos) {
          for (int k = 0; k < 4; k++) {
            int nx1 = x + dx[k], ny1 = y + dy[k];
            int nx2 = x + dx[(k + 1) % 4], ny2 = y + dy[(k + 1) % 4];
            if (nx1 < 0 || nx2 < 0 || nx1 >= n || nx2 >= n || ny1 < 0 ||
                ny2 < 0 || ny1 >= m || ny2 >= m)
              continue;
            if (grid[nx1][ny1] == grid[nx2][ny2] &&
                grid[nx1][ny1] == grid[x][y] &&
                grid[x + ddx[k]][y + ddy[k]] != grid[x][y]) {
              perimeter++;
            }
          }
        }
        ret += area * perimeter;
        area = perimeter = 0;
        pos.clear();
      }
    }
  }
  cout << ret << '\n';
}
