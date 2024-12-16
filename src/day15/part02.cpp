#include "aoc2024/sol.hpp"

constexpr const array<char, 4> dir{'<', 'v', '>', '^'};
constexpr const array<int, 4> DX{0, 1, 0, -1};
constexpr const array<int, 4> DY{-1, 0, 1, 0};

vector<string> enlarge_grid(const vector<string> &grid) {
  vector<string> ret;
  for (const auto &row : grid) {
    ret.emplace_back();
    for (auto c : row) {
      if (c == '#')
        ret.back() += "##";
      else if (c == 'O')
        ret.back() += "[]";
      else if (c == '.')
        ret.back() += "..";
      else
        ret.back() += "@.";
    }
  }
  return ret;
}

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
  grid = enlarge_grid(grid);
  int n = int(grid.size()), m = int(grid[0].size());
  function<bool(int, int, int)> box_moveable = [&](int x, int y, int didx) {
    assert(grid[x][y] == '[');
    if (didx == 0) {
      if (y - 1 < 0 || grid[x][y - 1] == '#')
        return false;
      if (grid[x][y - 1] == '.')
        return true;
      return box_moveable(x, y - 2, didx);
    } else if (didx == 1) {
      if (x + 1 >= n || grid[x + 1][y] == '#' || grid[x + 1][y + 1] == '#') {
        return false;
      }
      if (grid[x + 1][y] == '.' && grid[x + 1][y + 1] == '.') {
        return true;
      }
      bool ret = true;
      if (grid[x + 1][y] == '[') {
        ret = ret && box_moveable(x + 1, y, didx);
      } else if (grid[x + 1][y] == ']') {
        ret = ret && box_moveable(x + 1, y - 1, didx);
      }
      if (grid[x + 1][y + 1] == '[') {
        ret = ret && box_moveable(x + 1, y + 1, didx);
      } else if (grid[x + 1][y + 1] == ']') {
        ret = ret && box_moveable(x + 1, y, didx);
      }
      return ret;
    } else if (didx == 2) {
      if (y + 2 >= m || grid[x][y + 2] == '#')
        return false;
      if (grid[x][y + 2] == '.')
        return true;
      return box_moveable(x, y + 2, didx);
    } else {
      if (x - 1 < 0 || grid[x - 1][y] == '#' || grid[x - 1][y + 1] == '#') {
        return false;
      }
      if (grid[x - 1][y] == '.' && grid[x - 1][y + 1] == '.') {
        return true;
      }
      bool ret = true;
      if (grid[x - 1][y] == '[') {
        ret = ret && box_moveable(x - 1, y, didx);
      } else if (grid[x - 1][y] == ']') {
        ret = ret && box_moveable(x - 1, y - 1, didx);
      }
      if (grid[x - 1][y + 1] == '[') {
        ret = ret && box_moveable(x - 1, y + 1, didx);
      } else if (grid[x - 1][y + 1] == ']') {
        ret = ret && box_moveable(x - 1, y, didx);
      }
      return ret;
    }
  };
  function<bool(int, int, int)> shift_box = [&](int x, int y, int didx) {
    if (grid[x][y] == '.')
      return true;
    assert(grid[x][y] == '[');
    if (box_moveable(x, y, didx)) {
      if (didx == 0) {
        if (grid[x][y - 1] != '.') {
          assert(grid[x][y - 1] == ']');
          shift_box(x, y - 2, didx);
        }
        assert(grid[x][y - 1] == '.');
        swap(grid[x][y], grid[x][y - 1]);
        swap(grid[x][y], grid[x][y + 1]);
        return true;
      } else if (didx == 1) {
        if (grid[x + 1][y] == '[') {
          shift_box(x + 1, y, didx);
        } else if (grid[x + 1][y] == ']') {
          shift_box(x + 1, y - 1, didx);
        }

        if (grid[x + 1][y + 1] == '[') {
          shift_box(x + 1, y + 1, didx);
        } else if (grid[x + 1][y + 1] == ']') {
          shift_box(x + 1, y, didx);
        }

        assert(grid[x + 1][y] == '.');
        assert(grid[x + 1][y + 1] == '.');
        swap(grid[x][y], grid[x + 1][y]);
        swap(grid[x][y + 1], grid[x + 1][y + 1]);
        return true;
      } else if (didx == 2) {
        if (grid[x][y + 2] != '.') {
          assert(grid[x][y + 2] == '[');
          shift_box(x, y + 2, didx);
        }
        assert(grid[x][y + 2] == '.');
        swap(grid[x][y + 2], grid[x][y + 1]);
        swap(grid[x][y], grid[x][y + 1]);
        return true;
      } else {
        if (grid[x - 1][y] == '[') {
          shift_box(x - 1, y, didx);
        } else if (grid[x - 1][y] == ']') {
          shift_box(x - 1, y - 1, didx);
        }

        if (grid[x - 1][y + 1] == '[') {
          shift_box(x - 1, y + 1, didx);
        } else if (grid[x - 1][y + 1] == ']') {
          shift_box(x - 1, y, didx);
        }

        assert(grid[x - 1][y] == '.');
        assert(grid[x - 1][y + 1] == '.');
        swap(grid[x][y], grid[x - 1][y]);
        swap(grid[x][y + 1], grid[x - 1][y + 1]);
        return true;
      }
    }
    return false;
  };
  function<pair<int, int>(int, int, int)> shift = [&](int x, int y, int didx) {
    auto nx = x + DX[didx], ny = y + DY[didx];
    if (nx < 0 || ny < 0 || nx >= n || ny >= m)
      return make_pair(x, y);
    if (grid[nx][ny] == '#')
      return make_pair(x, y);
    if (grid[nx][ny] == '[') {
      if (shift_box(nx, ny, didx)) {
        grid[nx][ny] = grid[x][y];
        grid[x][y] = '.';
        return make_pair(nx, ny);
      }
      return make_pair(x, y);
    }
    if (grid[nx][ny] == ']') {
      if (shift_box(nx, ny - 1, didx)) {
        grid[nx][ny] = grid[x][y];
        grid[x][y] = '.';
        return make_pair(nx, ny);
      }
      return make_pair(x, y);
    }
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
    tie(x, y) = shift(x, y, idx);
  }
  int ret = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == '[') {
        ret += i * 100 + j;
      }
    }
  }
  cout << ret << '\n';
}
