// acmicpc 10277
//
// segment tree with lazy propagate

#include <bits/stdc++.h>
using namespace std;

typedef int val_t;

struct Operators {
    val_t (*combine)(val_t, val_t);
    val_t (*lazy_combine)(val_t, val_t);
    val_t (*update)(val_t, val_t);
    val_t (*repeat)(val_t, int);
};

struct SegmentTree {
    SegmentTree(int n, val_t init_val, val_t def_val, Operators ops) : n(n), init_val(init_val), def_val(def_val), t(4 * n + 1, init_val), lz(4 * n + 1, init_val), ops(ops) {}

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
        t[idx] = ops.combine(res1, res2);
        return t[idx];
    }

    val_t query(int ql, int qr) {
        return query(ql, qr, 1, 1, n + 1);
    }
    val_t query(int ql, int qr, int idx, int l, int r) {
        propagate(idx, l, r);
        if (l >= qr || r <= ql || l >= r) {
            return def_val;
        }
        if (ql <= l && r <= qr) {
            return t[idx];
        }
        int len = r - l;
        val_t res1 = query(ql, qr, idx * 2 + 0, l, l + len / 2);
        val_t res2 = query(ql, qr, idx * 2 + 1, l + len / 2, r);
        return ops.combine(res1, res2);
    }

    void propagate(int idx, int l, int r) {
        if (lz[idx] != init_val) {
            int len = r - l;
            t[idx] = ops.update(t[idx], ops.repeat(lz[idx], len));
            if (len > 1) {
                lz[idx * 2] = ops.lazy_combine(lz[idx * 2], lz[idx]);
                lz[idx * 2 + 1] = ops.lazy_combine(lz[idx * 2 + 1], lz[idx]);
            }
            lz[idx] = init_val;
        }
    }

    int n;
    val_t init_val;
    val_t def_val;
    vector<val_t> t;
    vector<val_t> lz;
    Operators ops;

    static val_t min(val_t a, val_t b) { return a < b ? a : b; }
    static val_t max(val_t a, val_t b) { return a > b ? a : b; }
    static val_t add(val_t a, val_t b) { return a + b; }
    static val_t xorop(val_t a, val_t b) { return a ^ b; }
    static val_t assign(val_t a, val_t b) { return b; }
    static val_t no_repeat(val_t a, int r) { return a; }
    static val_t times_repeat(val_t a, int r) { return r * a; }
    static val_t xor_repeat(val_t a, int r) { return (r & 1) ? a : 0; }
};


int C, N, O;

int groupchange(SegmentTree& mnst, SegmentTree& mxst, int a, int b, int s) {
    if (s == 0) return 0;
    if (s > 0) {
        int ss = min(s, N - mxst.query(a, b + 1));
        mxst.update(a, b + 1, ss);
        mnst.update(a, b + 1, ss);
        return ss;
    } else {
        int ss = max(s, -mnst.query(a, b + 1));
        mxst.update(a, b + 1, ss);
        mnst.update(a, b + 1, ss);
        return ss;
    }
}

int change(SegmentTree& mnst, SegmentTree& mxst, int x, int s) {
    return groupchange(mnst, mxst, x, x, s);
}


int main() {
    scanf("%d%d%d", &C, &N, &O);

    SegmentTree mnst(C, 0, N, { SegmentTree::min, SegmentTree::add, SegmentTree::add, SegmentTree::no_repeat });
    SegmentTree mxst(C, 0, 0, { SegmentTree::max, SegmentTree::add, SegmentTree::add, SegmentTree::no_repeat });

    for (int i = 0; i < O; ++i) {
        char cmd[12];
        int a, b, x, s;
        scanf("%s", cmd);
        if (cmd[0] == 'c') {
            scanf("%d%d", &x, &s);
            printf("%d\n", change(mnst, mxst, x + 1, s));
        } else if (cmd[0] == 'g') {
            scanf("%d%d%d", &a, &b, &s);
            printf("%d\n", groupchange(mnst, mxst, a + 1, b + 1, s));
        } else {
            scanf("%d", &x);
            printf("%d\n", mnst.query(x + 1, x + 2));
        }
    }
    return 0;
}
