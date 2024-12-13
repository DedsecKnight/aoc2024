#include "aoc2024/sol.hpp"

pair<int, int> parse_button(const string &line) {
  auto idx = line.find('+');
  auto cidx = line.find(',');
  int p1 = stoi(line.substr(idx + 1, cidx - idx - 1));
  idx = line.find('+', cidx);
  int p2 = stoi(line.substr(idx + 1, line.size() - 1 - idx));
  return make_pair(p1, p2);
}

pair<int, int> parse_prize(const string &line) {
  auto idx = line.find('=');
  auto cidx = line.find(',');
  int p1 = stoi(line.substr(idx + 1, cidx - idx - 1));
  idx = line.find('=', cidx);
  int p2 = stoi(line.substr(idx + 1, line.size() - 1 - idx));
  return make_pair(p1, p2);
}

SOLUTION {
  string line;
  int ret = 0;
  while (getline(cin, line)) {
    auto ba = parse_button(line);
    getline(cin, line);
    auto bb = parse_button(line);
    getline(cin, line);
    auto p = parse_prize(line);
    getline(cin, line);
    map<pair<int, int>, int> dist;
    dist[make_pair(0, 0)] = 0;
    deque<pair<int, int>> q;
    q.emplace_back(0, 0);
    while (!q.empty()) {
      auto [i, j] = q.front();
      q.pop_front();
      if (i > p.first || j > p.second)
        continue;
      if (i == p.first && j == p.second) {
        ret += dist[make_pair(i, j)];
        break;
      }
      auto neighbor = make_pair(i + ba.first, j + ba.second);
      int nd = dist.find(neighbor) != dist.end() ? dist[neighbor] : 1e9 + 10;
      if (nd > dist[make_pair(i, j)] + 3) {
        dist[neighbor] = dist[make_pair(i, j)] + 3;
        q.push_back(neighbor);
      }
      neighbor = make_pair(i + bb.first, j + bb.second);
      nd = dist.find(neighbor) != dist.end() ? dist[neighbor] : 1e9 + 10;
      if (nd > dist[make_pair(i, j)] + 1) {
        dist[neighbor] = dist[make_pair(i, j)] + 1;
        q.push_front(neighbor);
      }
    }
  }
  cout << ret << '\n';
}
