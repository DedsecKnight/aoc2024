#include "aoc2024/sol.hpp"

constexpr const array<int, 4> dx{-1, 0, 1, 0};
constexpr const array<int, 4> dy{0, 1, 0, -1};

SOLUTION {
  vector<string> grid;
  string line;
  while (getline(cin, line)) {
    if (line == "")
      break;
    grid.push_back(line);
  }
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
    assert(q.empty());
    auto i = curr / m, j = curr % m;
    size_t nx, ny;
    bool finished = false;
    int iter = 0;
    while (true) {
      nx = i + dx[dir], ny = j + dy[dir];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
        finished = true;
        break;
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
    }
  }
  int ret = 0, tmp_cnt = 0;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      if (any_of(visited[i * m + j].begin(), visited[i * m + j].end(),
                 [](auto x) { return x; })) {
        ret++;
      } else if (grid[i][j] == '.') {
        bool ff = false;
        for (size_t k = 0; k < 4; k++) {
          auto nx = i + dx[k], ny = j + dy[k];
          if (nx < 0 || ny < 0 || nx >= n || ny >= m)
            continue;
          if (any_of(visited[nx * m + ny].begin(), visited[nx * m + ny].end(),
                     [](auto x) { return x; })) {
            ff = true;
          }
        }
        tmp_cnt += ff;
      }
    }
  }
  cout << tmp_cnt << '\n';
  cout << ret << '\n';
}
