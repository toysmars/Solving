// Segment tree
//
// Example
//  * https://www.acmicpc.net/problem/10868
//  * https://www.acmicpc.net/problem/23744

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef i64 val_t;

// Segment tree
// The index of the first element should be 1.
struct SegmentTree {
    SegmentTree(int n, val_t def_val, val_t (*op)(val_t, val_t)) : n(n), def_val(def_val), t(4 * n + 1, def_val), op(op) {}

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
            t[idx] = x;
            return t[idx];
        }
        val_t res1 = update(i, x, idx * 2 + 0, l, l + len / 2);
        val_t res2 = update(i, x, idx * 2 + 1, l + len / 2, r);
        t[idx] = op(res1, res2);
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
        return op(res1, res2);
    }

    static val_t min(val_t a, val_t b) { return a < b ? a : b; }
    static val_t max(val_t a, val_t b) { return a > b ? a : b; }
    static val_t sum(val_t a, val_t b) { return a + b; }

    int n;
    val_t def_val;
    vector<val_t> t;
    val_t (*op)(val_t, val_t);
};
