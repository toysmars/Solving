// acmicpc 10999
//
// Fenwick tree with lazy propagation
// Range update and range sum

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

// Fenwick tree with lazy propagation that supports range update and range query.
// The index starts with 1 (not 0 based).
class RangeFenwick {
public:
    RangeFenwick(int n) : n(n), d(n + 1), c(n + 1) {}

    // increases numbers in range [l, r) by x
    void increase(int l, int r, i64 x) {
        increase(d, l, x);
        increase(d, r, -x);
        increase(c, l, (1 - l) * x);
        increase(c, r, (r - 1) * x);
    }

    // cacluates sum of number in range [l, r)
    i64 sum(int l, int r) {
        return sum(d, r - 1) * (r - 1) + sum(c, r - 1) - sum(d, l - 1) * (l - 1) - sum(c, l - 1);
    }

private:
    void increase(vector<i64>& tree, int i, i64 x) {
        for (; i <= n; i += (i & -i)) tree[i] += x;
    }

    // sum tree[1..i]
    i64 sum(vector<i64>& tree, int i) {
        i64 res = 0;
        for (; i > 0; i -= (i & -i)) res += tree[i];
        return res;
    }

    int n;
    vector<i64> d;
    vector<i64> c;
};

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    RangeFenwick rf(n);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        rf.increase(i, i + 1, x);
    }
    for (int i = 0; i < m + k; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (a == 1) {
            i64 d;
            scanf("%lld", &d);
            rf.increase(b, c + 1, d);
        } else {
            printf("%lld\n", rf.sum(b, c + 1));
        }
    }
}
