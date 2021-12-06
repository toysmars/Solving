// acmicpc 10167
//
// segment ree
// maximum range sum

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

struct RangeSum {
    i64 lsum;
    i64 msum;
    i64 rsum;
    i64 tsum;
};

typedef RangeSum val_t;

struct Operations {
    val_t (*combine)(val_t, val_t);
    val_t (*update)(val_t, val_t);
};

// Segment tree
// The index of the first element should be 1.
struct SegmentTree {
    SegmentTree(int n, val_t def_val, Operations ops) : n(n), def_val(def_val), t(4 * n + 1, def_val), ops(ops) {}

    // Update the value of `i`th element to `x`.
    void update(int i, val_t x) {
        update(i, x, 1, 1, n + 1);
    }
    val_t update(int i, val_t x, int idx, int l, int r) {
        if (l > i || r <= i || l >= r) {
            return t[idx];
        }
        int len = r - l;
        if (len == 1) {
            t[idx] = ops.update(t[idx], x);
            return t[idx];
        }
        val_t res1 = update(i, x, idx * 2 + 0, l, l + len / 2);
        val_t res2 = update(i, x, idx * 2 + 1, l + len / 2, r);
        t[idx] = ops.combine(res1, res2);
        return t[idx];
    }
    // Query the value elements in range [ql, qr).
    val_t query(int ql, int qr) {
        return query(ql, qr, 1, 1, n + 1);
    }
    val_t query(int ql, int qr, int idx, int l, int r) {
        if (l >= qr || r <= ql || l >= r) {
            return def_val;
        }
        if (ql <= l && qr >= r) {
            return t[idx];
        }
        int len = r - l;
        val_t res1 = query(ql, qr, idx * 2 + 0, l, l + len / 2);
        val_t res2 = query(ql, qr, idx * 2 + 1, l + len / 2, r);
        return ops.combine(res1, res2);
    }

    int n;
    val_t def_val;
    vector<val_t> t;
    Operations ops;
};

RangeSum combine(RangeSum a, RangeSum b) {
    return {
        .lsum = max(a.lsum, a.tsum + b.lsum),
        .msum = max({ a.msum, b.msum, a.rsum + b.lsum }),
        .rsum = max(b.rsum, b.tsum + a.rsum),
        .tsum = a.tsum + b.tsum
    };
}

RangeSum assign(RangeSum a, RangeSum b) {
    return {
        a.lsum + b.lsum,
        a.msum + b.msum,
        a.rsum + b.rsum,
        a.tsum + b.tsum
    };
}

int main() {
    int n;
    scanf("%d", &n);

    map<int, vector<pair<int, int>>> ygms;
    set<int> yset, xset;
    for (int i = 0; i < n; ++i) {
        int x, y, v;
        scanf("%d%d%d", &x, &y, &v);
        ygms[y].emplace_back(x, v);
        yset.insert(y);
        xset.insert(x);
    }
    int xcnt = 0;
    map<int, int> xidx;
    vector<int> ys, xs;
    for (auto y: yset) ys.push_back(y);
    for (auto x: xset) xidx[x] = ++xcnt;

    i64 ans = 0;
    for (int i = 0; i < ys.size(); ++i) {
        SegmentTree st(xcnt, { 0, 0, 0, 0 }, { combine, assign });
        for (int j = i; j < ys.size(); ++j) {
            for (auto gm: ygms[ys[j]]) {
                int v = gm.second;
                st.update(xidx[gm.first], { v, v, v, v });
            }
            auto res = st.query(1, xcnt + 1);
            auto sum = max({ res.lsum, res.msum, res.rsum, res.tsum });
            ans = max(ans, sum);
            //printf("%d(%d), %d(%d) -> %lld\n", i, ys[i], j, ys[j], sum);
        }
    }
    printf("%lld\n", ans);

    return 0;
}
