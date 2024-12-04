#include "aoc2024/sol.hpp"

SOLUTION {
  vector<string> grid;
  string line;
  while (cin >> line) {
    grid.push_back(line);
  }
  size_t n = grid.size(), m = grid[0].size();
  int ret = 0;
  for (size_t i = 1; i + 1 < n; i++) {
    for (size_t j = 1; j + 1 < m; j++) {
      if (grid[i][j] == 'A') {
        string t1{}, t2{};
        t1 += grid[i - 1][j - 1];
        t1 += grid[i][j];
        t1 += grid[i + 1][j + 1];

        t2 += grid[i - 1][j + 1];
        t2 += grid[i][j];
        t2 += grid[i + 1][j - 1];

        ret += (t1 == "MAS" || t1 == "SAM") && (t2 == "MAS" || t2 == "SAM");
      }
    }
  }
  cout << ret << '\n';
}
