#include "aoc2024/sol.hpp"

SOLUTION {
  string s;
  cin >> s;
  vector<string> mem;
  int empty_slot = 0;
  for (int i = 0, c = 0; i < int(s.size()); i += 2, c++) {
    for (int j = 0; j < s[i] - '0'; j++) {
      mem.push_back(to_string(c));
    }
    for (int j = 0; j < s[i + 1] - '0'; j++) {
      mem.push_back(".");
      empty_slot++;
    }
  }
  int ptr1 = 0, ptr2 = int(mem.size()) - 1;
  for (int iter = 0; iter < empty_slot; iter++) {
    while (ptr1 < int(mem.size()) && mem[ptr1] != ".") {
      ptr1++;
    }
    while (ptr2 >= 0 && mem[ptr2] == ".") {
      ptr2--;
    }
    if (ptr1 > ptr2)
      break;
    assert(ptr1 != ptr2);
    swap(mem[ptr1], mem[ptr2]);
  }
  ll ret = 0;
  for (size_t i = 0; i < mem.size(); i++) {
    if (mem[i] == ".")
      break;
    ret += i * 1ll * stoll(mem[i]);
  }
  cout << ret << '\n';
}
