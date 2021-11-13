// acmicpc 3653
//
// fenwick tree
// segment tree
// range sum
// prefix sum
// 구간합

#include <bits/stdc++.h>
using namespace std;

class Fenwick {
  public:
    Fenwick(int n) : n(n), f(n + 1) {}

    // [i] += x
    void increase(int i, int x) {
        for (; i <= n; i += (i & -i)) f[i] += x;
    }

    // sum [1..i]
    int sum(int i) {
        int res = 0;
        for (; i > 0; i -= (i & -i)) res += f[i];
        return res;
    }

    // sum [l..r)
    int sum(int l, int r) {
        return sum(r - 1) - sum(l - 1);
    }

  private:
    int n;
    vector<int> f;
};

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        Fenwick fenwick(n + m + 1);
        vector<int> pos(n + 1);
        for (int i = 1; i <= n; ++i) {
            fenwick.increase(i, 1);
            pos[i] = n - i + 1;
        }
        for (int i = 1; i <= m; ++i) {
            int q;
            scanf("%d", &q);
            printf("%d ", fenwick.sum(pos[q] + 1, n + i));
            fenwick.increase(pos[q], -1);
            pos[q] = n + i;
            fenwick.increase(pos[q], 1);
        }
        printf("\n");
    }
    return 0;
}
