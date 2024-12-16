#include "aoc2024/sol.hpp"

constexpr const array<char, 4> dir{'<', 'v', '>', '^'};
constexpr const array<int, 4> DX{0, 1, 0, -1};
constexpr const array<int, 4> DY{-1, 0, 1, 0};

SOLUTION {
  vector<string> grid;
  string line, instruction;
  while (getline(cin, line)) {
    if (line == "") {
      break;
    }
    grid.push_back(line);
  }
  while (getline(cin, line)) {
    instruction += line;
  }
  int n = int(grid.size()), m = int(grid[0].size());
  function<pair<int, int>(int, int, int, int)> shift = [&](int x, int y, int dx,
                                                           int dy) {
    auto nx = x + dx, ny = y + dy;
    if (nx < 0 || ny < 0 || nx >= n || ny >= m)
      return make_pair(x, y);
    if (grid[nx][ny] == '#')
      return make_pair(x, y);
    if (grid[nx][ny] == 'O') {
      shift(nx, ny, dx, dy);
      if (grid[nx][ny] == '.') {
        grid[nx][ny] = grid[x][y];
        grid[x][y] = '.';
        return make_pair(nx, ny);
      }
      return make_pair(x, y);
    };
    swap(grid[x][y], grid[nx][ny]);
    return make_pair(nx, ny);
  };
  int x, y;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == '@') {
        x = i, y = j;
        break;
      }
    }
  }
  for (char c : instruction) {
    auto idx = find(dir.begin(), dir.end(), c) - dir.begin();
    tie(x, y) = shift(x, y, DX[idx], DY[idx]);
  }
  int ret = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 'O') {
        ret += i * 100 + j;
      }
    }
  }
  cout << ret << '\n';
}
