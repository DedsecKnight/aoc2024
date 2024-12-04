#include "aoc2024/sol.hpp"

constexpr const array<int, 8> dx{-1, 1, 0, 0, 1, 1, -1, -1};
constexpr const array<int, 8> dy{0, 0, -1, 1, 1, -1, 1, -1};

SOLUTION {
  vector<string> grid;
  string line;
  while (cin >> line) {
    grid.push_back(line);
  }
  size_t n = grid.size(), m = grid[0].size();
  int ret = 0;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      if (grid[i][j] == 'X') {
        for (size_t k = 0; k < 8; k++) {
          if (i + dx[k] * 3 >= 0 && i + dx[k] * 3 < n && j + dy[k] * 3 >= 0 &&
              j + dy[k] * 3 < m) {
            ret += grid[i + dx[k]][j + dy[k]] == 'M' &&
                   grid[i + dx[k] * 2][j + dy[k] * 2] == 'A' &&
                   grid[i + dx[k] * 3][j + dy[k] * 3] == 'S';
          }
        }
      }
    }
  }
  cout << ret << '\n';
}
