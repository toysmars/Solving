// acmicpc 18227
//
// Fenwick tree
// Tree traverse
// 트리를 펴서 구간쿼리

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

int order;
int vmn[200001];
int vmx[200001];
int d[200001];
void dfs(int u, int depth, const vector<vector<int>>& g) {
    if (d[u] > 0) return;
    d[u] = depth;
    vmn[u] = order + 1;
    for (int v: g[u]) {
        dfs(v, depth + 1, g);
    }
    vmx[u] = ++order;
}

int main() {
    int n, c;
    scanf("%d%d", &n, &c);
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(c, 1, g);
    Fenwick ft(n + 1);
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int q, x;
        scanf("%d%d", &q, &x);
        if (q == 1) {
            ft.increase(vmx[x], 1);
        } else {
            printf("%lld\n", d[x] * ft.sum(vmn[x], vmx[x] + 1));
        }
    }
    return 0;
}
