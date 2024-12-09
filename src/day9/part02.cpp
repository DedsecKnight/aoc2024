#include "aoc2024/sol.hpp"

struct file_t {
  int s, e, id;
};

struct block_t {
  int s, e, l;
};

SOLUTION {
  string s;
  cin >> s;
  vector<file_t> files, final_files;
  vector<block_t> blocks;
  int pos = 0;
  for (int i = 0, c = 0; i < int(s.size()); i += 2, c++) {
    files.push_back({.s = pos, .e = pos + int(s[i] - '0') - 1, .id = c});
    pos += s[i] - '0';
    blocks.push_back(
        {.s = pos, .e = pos + int(s[i + 1] - '0') - 1, .l = s[i + 1] - '0'});
    pos += s[i + 1] - '0';
  }
  for (int i = int(files.size()) - 1; i >= 0; i--) {
    for (int j = 0; j < int(blocks.size()); j++) {
      if (blocks[j].s > files[i].s) {
        final_files.push_back(files[i]);
        break;
      }
      if (blocks[j].l >= files[i].e - files[i].s + 1) {
        int sz = files[i].e - files[i].s + 1;
        blocks.push_back({.s = files[i].s,
                          .e = files[i].e,
                          .l = files[i].e - files[i].s + 1});
        if (blocks[j].s + sz <= blocks[j].e) {
          blocks.push_back({.s = blocks[j].s + sz,
                            .e = blocks[j].e,
                            .l = blocks[j].e - blocks[j].s - sz + 1});
        }
        final_files.push_back(
            {.s = blocks[j].s, .e = blocks[j].s + sz - 1, .id = files[i].id});
        blocks.erase(blocks.begin() + j);
        sort(blocks.begin(), blocks.end(),
             [&](const auto &x, const auto &y) { return x.s < y.s; });
        break;
      }
    }
  }
  ll ret = 0;
  for (auto elem : final_files) {
    for (int j = elem.s; j <= elem.e; j++) {
      ret += j * 1ll * elem.id;
    }
  }
  cout << ret << '\n';
}
