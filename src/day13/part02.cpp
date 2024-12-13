#include "aoc2024/sol.hpp"

typedef vector<double> vd;
const double eps = 1e-12;

int solveLinear(vector<vd> &A, vd &b, vd &x) {
  int n = int(A.size()), m = int(x.size()), rank = 0, br, bc;
  vector<int> col(m);
  iota(begin(col), end(col), 0);

  for (int i = 0; i < n; i++) {
    double v, bv = 0;
    for (int r = i; r < n; r++)
      for (int c = i; c < m; c++)
        if ((v = fabs(A[r][c])) > bv)
          br = r, bc = c, bv = v;
    if (bv <= eps) {
      for (int j = i; j < n; j++)
        if (fabs(b[j]) > eps)
          return -1;
      break;
    }
    swap(A[i], A[br]);
    swap(b[i], b[br]);
    swap(col[i], col[bc]);
    for (int j = 0; j < n; j++)
      swap(A[j][i], A[j][bc]);
    bv = 1 / A[i][i];
    for (int j = i + 1; j < n; j++) {
      double fac = A[j][i] * bv;
      b[j] -= fac * b[i];
      for (int k = i + 1; k < m; k++)
        A[j][k] -= fac * A[i][k];
    }
    rank++;
  }

  x.assign(m, 0);
  for (int i = rank; i--;) {
    b[i] /= A[i][i];
    x[col[i]] = b[i];
    for (int j = 0; j < i; j++)
      b[j] -= A[j][i] * b[i];
  }
  return rank; // (multiple solutions if rank < m)
}

pair<ll, ll> parse_button(const string &line) {
  auto idx = line.find('+');
  auto cidx = line.find(',');
  int p1 = stoi(line.substr(idx + 1, cidx - idx - 1));
  idx = line.find('+', cidx);
  int p2 = stoi(line.substr(idx + 1, line.size() - 1 - idx));
  return make_pair(p1, p2);
}

pair<ll, ll> parse_prize(const string &line) {
  auto idx = line.find('=');
  auto cidx = line.find(',');
  int p1 = stoi(line.substr(idx + 1, cidx - idx - 1));
  idx = line.find('=', cidx);
  int p2 = stoi(line.substr(idx + 1, line.size() - 1 - idx));
  return make_pair(p1 + 10000000000000ll, p2 + 10000000000000ll);
}

SOLUTION {
  string line;
  ll ret = 0;
  while (getline(cin, line)) {
    auto ba = parse_button(line);
    getline(cin, line);
    auto bb = parse_button(line);
    getline(cin, line);
    auto p = parse_prize(line);
    getline(cin, line);
    vector<vector<double>> A(2, vector<double>(2));
    vector<double> b(2), x(2);
    A[0][0] = ba.first, A[0][1] = bb.first;
    A[1][0] = ba.second, A[1][1] = bb.second;
    b[0] = (double)p.first, b[1] = (double)p.second;
    solveLinear(A, b, x);
    ll c1 = round(x[0]), c2 = round(x[1]);
    if (c1 * ba.first + c2 * bb.first == p.first &&
        c1 * ba.second + c2 * bb.second == p.second) {
      ret += c1 * 3 + c2;
    }
  }
  cout << ret << '\n';
}
