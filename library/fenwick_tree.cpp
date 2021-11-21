// Fenwick tree
// Examples:
//  * https://www.acmicpc.net/problem/3563
//  * https://www.acmicpc.net/problem/18227

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef i64 num_t;

class Fenwick {
  public:
    Fenwick(int n) : n(n), f(n + 1) {}

    // [i] += x
    void increase(int i, num_t x) {
        for (; i <= n; i += (i & -i)) f[i] += x;
    }

    // sum [1..i]
    num_t sum(int i) {
        num_t res = 0;
        for (; i > 0; i -= (i & -i)) res += f[i];
        return res;
    }

    // sum [l..r)
    num_t sum(int l, int r) {
        return sum(r - 1) - sum(l - 1);
    }

  private:
    int n;
    vector<num_t> f;
};
