// Persistent Segment Tree
//
// Examples:
// * https://www.acmicpc.net/problem/11012

#include <bits/stdc++.h>
using namespace std;

typedef int val_t;
typedef int idx_t;

// Node represents a node in a segment tree range in [`l`, `r`) with value `x`.
struct Node {
    val_t x;
    idx_t lc;
    idx_t rc;
};

struct Operations {
    val_t (*combine)(val_t, val_t);
    val_t (*set)(val_t, val_t);
};

// Persistent Segment tree
// The index of the first element should be 1.
struct PersistentSegmentTree {
    PersistentSegmentTree(int n, int m, val_t def_val, Operations ops, const vector<val_t>& init) : n(n), def_val(def_val), ops(ops) {
        nodes.reserve(4 * (n + m) + 1);
        root.reserve(m + 1);
        root.push_back(initialize(1, n + 1, init).first);
    }

    pair<idx_t, val_t> initialize(int l, int r, const vector<val_t>& init) {
        if (l >= r) {
            return make_pair(-1, def_val);
        }
        int len = r - l;
        idx_t idx = nodes.size();
        nodes.push_back({init[l], -1, -1});
        if (len > 1) {
            auto res1 = initialize(l, l + len / 2, init);
            auto res2 = initialize(l + len / 2, r, init);
            nodes[idx].x = ops.combine(res1.second, res2.second);
            nodes[idx].lc = res1.first;
            nodes[idx].rc = res2.first;
        }
        return make_pair(idx, nodes[idx].x);;
    }

    // Update the value of `i`th element to `x` by creating a new tree.
    // Returns the new segment tree creation time.
    idx_t update(int i, val_t x) {
        auto res = update(i, x, root[root.size() - 1], 1, n + 1);
        root.push_back(res.first);
        return root.size() - 1;
    }
    pair<idx_t, val_t> update(int i, val_t x, idx_t idx, int l, int r) {
        if (l > i || r <= i || l >= r) {
            return make_pair(idx, nodes[idx].x);
        }
        int new_idx = nodes.size();
        nodes.push_back(nodes[idx]);
        int len = r - l;
        if (len == 1) {
            nodes[new_idx].x = ops.set(nodes[new_idx].x, x);
        } else {
            auto res1 = update(i, x, nodes[idx].lc, l, l + len / 2);
            auto res2 = update(i, x, nodes[idx].rc, l + len / 2, r);
            nodes[new_idx].x = ops.combine(res1.second, res2.second);
            nodes[new_idx].lc = res1.first;
            nodes[new_idx].rc = res2.first;
        }
        return make_pair(new_idx, nodes[new_idx].x);
    }

    // Query the value elements in range [`ql`, `qr`) from a segment tree created at time `t`.
    val_t query(int t, int ql, int qr) {
        return query(ql, qr, root[t], 1, n + 1);
    }
    val_t query(int ql, int qr, int idx, int l, int r) {
        if (idx < 0 || l >= qr || r <= ql || l >= r) {
            return def_val;
        }
        if (ql <= l && qr >= r) {
            return nodes[idx].x;
        }
        int len = r - l;
        val_t res1 = query(ql, qr, nodes[idx].lc, l, l + len / 2);
        val_t res2 = query(ql, qr, nodes[idx].rc, l + len / 2, r);
        return ops.combine(res1, res2);
    }


    static val_t min(val_t a, val_t b) { return a < b ? a : b; }
    static val_t max(val_t a, val_t b) { return a > b ? a : b; }
    static val_t sum(val_t a, val_t b) { return a + b; }
    static val_t assign(val_t a, val_t b) { return b; }

    int n;
    val_t def_val;
    Operations ops;
    vector<Node> nodes;
    vector<int> root;
};

const int MAX_X = 100001;
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        PersistentSegmentTree pst(MAX_X, n, 0, { PersistentSegmentTree::sum, PersistentSegmentTree::sum }, vector<int>(MAX_X + 1));
        vector<vector<int>> eggs(MAX_X + 1);
        vector<int> root(MAX_X + 1);
        for (int i = 0; i < n; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            x++; y++;
            eggs[y].push_back(x);
        }
        root[0] = 0;
        for (int y = 1; y <= MAX_X; ++y) {
            for (int x: eggs[y]) {
                root[y] = pst.update(x, 1);
            }
            root[y] = max(root[y], root[y - 1]);
        }
        long long ans = 0;
        for (int i = 0; i < m; ++i) {
            int l, r, b, t;
            scanf("%d%d%d%d", &l, &r, &b, &t);
            l++; r++; b++; t++;
            ans += pst.query(root[t], l, r + 1) - pst.query(root[b - 1], l, r + 1);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
