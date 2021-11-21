// acmicpc 2336
//
// SegmentTree
// RMQ

#include <bits/stdc++.h>
using namespace std;

typedef int val_t;
const val_t DEFAULT = 1000000;

struct SegmentTree {
    SegmentTree(int n, val_t (*op)(val_t, val_t)) : n(n), t(4 * n + 1, DEFAULT), op(op) {}

    void update(int i, val_t x) {
        update(i, x, 1, 1, n + 1);
    }
    val_t update(int i, val_t x, int idx, int l, int r) {
        if (l > i || r <= i || l >= r) {
            return DEFAULT;
        }
        int len = r - l;
        if (len == 1) {
            t[idx] = x;
            return t[idx];
        }
        val_t res1 = update(i, x, idx * 2 + 0, l, l + len / 2);
        val_t res2 = update(i, x, idx * 2 + 1, l + len / 2, r);
        t[idx] = op(t[idx], op(res1, res2));
        return t[idx];
    }
    val_t query(int ql, int qr) {
        return query(ql, qr, 1, 1, n + 1);
    }
    val_t query(int ql, int qr, int idx, int l, int r) {
        if (l >= qr || r <= ql || l >= r) {
            return DEFAULT;
        }
        if (ql <= l && qr >= r) {
            return t[idx];
        }
        int len = r - l;
        val_t res1 = query(ql, qr, idx * 2 + 0, l, l + len / 2);
        val_t res2 = query(ql, qr, idx * 2 + 1, l + len / 2, r);
        return op(res1, res2);
    }

    static val_t min(val_t a, val_t b) { return a < b ? a : b; }
    static val_t max(val_t a, val_t b) { return a < b ? a : b; }

    int n;
    vector<val_t> t;
    val_t (*op)(val_t, val_t);
};

int main() {
    int n, x;
    scanf("%d", &n);
    vector<pair<int, pair<int, int>>> S(n + 1);
    for (int i = 1; i <= n; ++i) { scanf("%d", &x); S[x].first = i; }
    for (int i = 1; i <= n; ++i) { scanf("%d", &x); S[x].second.first = i; }
    for (int i = 1; i <= n; ++i) { scanf("%d", &x); S[x].second.second = i; }
    sort(S.begin(), S.end());
    SegmentTree st(S.size(), SegmentTree::min);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int b = S[i].second.first;
        int c = S[i].second.second;
        st.update(b, c);
        int minC = st.query(1, b);
        ans += (minC == DEFAULT || minC > c);
    }
    printf("%d\n", ans);
    return 0;
}
