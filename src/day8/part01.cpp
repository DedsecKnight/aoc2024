#include "aoc2024/sol.hpp"

SOLUTION {
  vector<string> grid;
  string line;
  unordered_map<char, vector<pair<int, int>>> buckets;
  size_t n = 0;
  while (cin >> line) {
    grid.push_back(line);
    for (size_t j = 0; j < line.size(); j++) {
      if (line[j] != '.')
        buckets[line[j]].emplace_back(n, j);
    }
    n++;
  }
  size_t m = grid[0].size();
  vector<vector<bool>> marked(n, vector<bool>(m));
  auto mark = [&](int i, int j) {
    if (i >= 0 && i < n && j >= 0 && j < m) {
      marked[i][j] = true;
    }
  };
  for (const auto &[_, bucket] : buckets) {
    for (size_t i = 0; i < bucket.size(); i++) {
      for (size_t j = i + 1; j < bucket.size(); j++) {
        auto dx = abs(bucket[i].first - bucket[j].first);
        auto dy = abs(bucket[i].second - bucket[j].second);
        if (bucket[i].first < bucket[j].first) {
          if (bucket[i].second < bucket[j].second) {
            mark(bucket[i].first - dx, bucket[i].second - dy);
            mark(bucket[j].first + dx, bucket[j].second + dy);
          } else if (bucket[i].second > bucket[j].second) {
            mark(bucket[i].first - dx, bucket[i].second + dy);
            mark(bucket[j].first + dx, bucket[j].second - dy);
          } else {
            mark(bucket[i].first - dx, bucket[i].second);
            mark(bucket[j].first + dx, bucket[j].second);
          }
        } else if (bucket[i].first > bucket[j].first) {
          if (bucket[i].second < bucket[j].second) {
            mark(bucket[i].first + dx, bucket[i].second - dy);
            mark(bucket[j].first - dx, bucket[j].second + dy);
          } else if (bucket[i].second > bucket[j].second) {
            mark(bucket[i].first + dx, bucket[i].second + dy);
            mark(bucket[j].first - dx, bucket[j].second - dy);
          } else {
            mark(bucket[i].first + dx, bucket[i].second);
            mark(bucket[j].first - dx, bucket[j].second);
          }
        } else {
          mark(bucket[i].first, min(bucket[i].second, bucket[j].second) - dy);
          mark(bucket[i].first, max(bucket[i].second, bucket[j].second) + dy);
        }
      }
    }
  }
  int ret = 0;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      ret += marked[i][j];
    }
  }
  cout << ret << '\n';
}
