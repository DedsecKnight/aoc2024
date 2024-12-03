#include "aoc2024/sol.hpp"

ll eval(const string &s) {
  int fidx = s.find('(');
  int cidx = s.find(',', fidx + 1);
  int sidx = s.find(')', cidx);
  return stoll(s.substr(fidx + 1, cidx - 1 - fidx)) *
         stoll(s.substr(cidx + 1, sidx - 1 - cidx));
}

SOLUTION {
  string s{}, line;
  while (cin >> line) {
    s += line;
  }
  regex rgx{"mul\\([0-9]+,[0-9]+\\)|do\\(\\)|don\\'t\\(\\)"};
  auto words_begin = sregex_iterator(s.begin(), s.end(), rgx);
  auto words_end = sregex_iterator();
  bool enabled = true;
  ll ret = 0;
  for (auto it = words_begin; it != words_end; it++) {
    if (it->str() == "do()")
      enabled = true;
    else if (it->str() == "don't()")
      enabled = false;
    else
      ret += eval(it->str()) * enabled;
  }
  cout << ret << '\n';
}
