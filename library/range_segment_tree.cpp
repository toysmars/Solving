// Segment Tree with Lazy Propagation
// RMQ
// 
// Examples:
//  * https://www.acmicpc.net/problem/12844
//  * https://www.acmicpc/net/problem/13925
//  * https://www.acmicpc/net/problem/13510

#include <bits/stdc++.h>
using namespace std;

typedef int val_t;

const val_t DEFAULT = 0;
typedef val_t (*BiOperator)(val_t, val_t);
typedef val_t (*SetOperator)(val_t, val_t);
typedef val_t (*RepeatOperator)(val_t, int);

struct SegmentTree {
    SegmentTree() {}
    SegmentTree(int n, BiOperator op, SetOperator sop, RepeatOperator rop) : n(n), t(4 * n + 1, DEFAULT), lz(4 * n + 1, DEFAULT), op(op), sop(sop), rop(rop) {}

    // update the segment tree with value x for range [ul, ur)
    void update(int ul, int ur, val_t x) {
        update(ul, ur, x, 1, 1, n + 1);
    }
    val_t update(int ul, int ur, val_t x, int idx, int l, int r) {
        propagate(idx, l, r);
        if (l >= ur || r <= ul || l >= r) {
            return t[idx];
        }
        if (ul <= l && r <= ur) {
            lz[idx] = x;
            propagate(idx, l, r);
            return t[idx];
        }
        int len = r - l;
        val_t res1 = update(ul, ur, x, idx * 2 + 0, l, l + len / 2);
        val_t res2 = update(ul, ur, x, idx * 2 + 1, l + len / 2, r);
        t[idx] = op(res1, res2);
        return t[idx];
    }

    val_t query(int ql, int qr) {
        return query(ql, qr, 1, 1, n + 1);
    }
    val_t query(int ql, int qr, int idx, int l, int r) {
        propagate(idx, l, r);
        if (l >= qr || r <= ql || l >= r) {
            return DEFAULT;
        }
        if (ql <= l && r <= qr) {
            return t[idx];
        }
        int len = r - l;
        val_t res1 = query(ql, qr, idx * 2 + 0, l, l + len / 2);
        val_t res2 = query(ql, qr, idx * 2 + 1, l + len / 2, r);
        return op(res1, res2);
    }

    void propagate(int idx, int l, int r) {
        if (lz[idx] != DEFAULT) {
            int len = r - l;
            t[idx] = sop(t[idx], rop(lz[idx], len));
            if (len > 1) {
                lz[idx * 2] = op(lz[idx * 2], lz[idx]);
                lz[idx * 2 + 1] = op(lz[idx * 2 + 1], lz[idx]);
            }
            lz[idx] = DEFAULT;
        }
    }

    int n;
    vector<val_t> t;
    vector<val_t> lz;
    BiOperator op;
    SetOperator sop;
    RepeatOperator rop;

    static val_t min(val_t a, val_t b) { return a < b ? a : b; }
    static val_t min_set(val_t a, val_t b) { return b; }
    static val_t min_repeat(val_t a, int r) { return a; }

    static val_t max(val_t a, val_t b) { return a > b ? a : b; }
    static val_t max_set(val_t a, val_t b) { return b; }
    static val_t max_repeat(val_t a, int r) { return a; }

    static val_t add(val_t a, val_t b) { return a + b; }
    static val_t add_set(val_t a, val_t b) { return a + b; }
    static val_t add_repeat(val_t a, int r) { return r * a; }

    static val_t xor_bi(val_t a, val_t b) { return a ^ b; }
    static val_t xor_set(val_t a, val_t b) { return a ^ b; }
    static val_t xor_repeat(val_t a, int r) { return (r & 1) ? a : 0; }
};

