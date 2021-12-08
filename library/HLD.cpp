// HLD
// Heavy Light Decomposition
// Segment tree
//
// Examples
//  * https://www.acmicpc.net/problem/13510
//  * https://www.acmicpc.net/problem/13309

#include <bits/stdc++.h>
using namespace std;

typedef int val_t;

struct Operators {
    val_t (*combine)(val_t, val_t);
    val_t (*update)(val_t, val_t);
    val_t (*lazy_update)(val_t, val_t);
    val_t (*repeat)(val_t, int);
};

struct SegmentTree {
    SegmentTree(int n, val_t def_val, Operators ops) : n(n), def_val(def_val), t(4 * n + 1, 0), lz(4 * n + 1, 0), haslz(4 * n + 1, false), ops(ops) {}

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
            haslz[idx] = true;
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
        if (haslz[idx]) {
            int len = r - l;
            t[idx] = ops.update(t[idx], ops.repeat(lz[idx], len));
            if (len > 1) {
                lz[idx * 2] = ops.lazy_update(lz[idx * 2], lz[idx]);
                haslz[idx * 2] = true;
                lz[idx * 2 + 1] = ops.lazy_update(lz[idx * 2 + 1], lz[idx]);
                haslz[idx * 2 + 1] = true;
            }
            haslz[idx] = false;
        }
    }

    int n;
    val_t def_val;
    vector<val_t> t;
    vector<val_t> lz;
    vector<bool> haslz;
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


// heavy-Light Decomposition solver
// Tree node index must be in range [1, N].
struct HeavyLightDecomposition {

    HeavyLightDecomposition(int n) : n(n), g(n+1), size(n+1), depth(n+1), parent(n+1), group(n+1), gidx(n+1) {}

    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void init() {
        group_cnt = 0;
        fill(group.begin(), group.end(), 0);
        fill(gidx.begin(), gidx.end(), 0);
        ghead.resize(1);
        gsize.resize(1);
    }

    void build(int root) {
        dfs(root, 0, 1);
        hld(root, 1);
    }

    int dfs(int cur, int p, int d) {
        size[cur] = 1;
        parent[cur] = p;
        depth[cur] = d;
        for (auto c: g[cur]) {
            if (p == c) {
                continue;
            }
            size[cur] += dfs(c, cur, d + 1);
        }
        return size[cur];
    }

    void hld(int cur, int idx) {
        if (idx == 1) {
            group_cnt += 1;
            ghead.push_back(cur);
            gsize.push_back(0);
        }
        group[cur] = group_cnt;
        gidx[cur] = idx;
        gsize[group_cnt] += 1;

        int heavy_child = 0;
        int heavy_size = 0;
        for (auto child: g[cur]) {
            if (child == parent[cur]) continue;
            if (heavy_size < size[child]) {
                heavy_size = size[child];
                heavy_child = child;
            }
        }
        if (heavy_child > 0) {
            hld(heavy_child, idx + 1);
        }
        for (auto child: g[cur]) {
            if (child == parent[cur]) continue;
            if (child == heavy_child) continue;
            hld(child, 1);
        }
    }

    int lca(int u, int v) {
        int uh = ghead[group[u]];
        int vh = ghead[group[v]];
        while (uh != vh) {
            if (depth[uh] > depth[vh]) {
                u = parent[uh];
                uh = ghead[group[u]];
            } else {
                v = parent[vh];
                vh = ghead[group[v]];
            }
        }
        return depth[u] < depth[v] ? u : v;
    }

    int n;
    int group_cnt;
    vector<vector<int>> g;
    vector<int> size;
    vector<int> depth;
    vector<int> parent;
    vector<int> group;
    vector<int> gidx;
    vector<int> ghead;
    vector<int> gsize;
};

struct HLDQuerier {
    HLDQuerier(HeavyLightDecomposition* hld, val_t def_val, Operators ops): hld(hld), val(hld->n+1), gst(), ops(ops) {
        gst.push_back(SegmentTree(0, def_val, ops));
        for (int gid = 1; gid <= hld->group_cnt; ++gid) {
            gst.push_back(SegmentTree(hld->gsize[gid], def_val, ops));
        }
    }

    void update(int u, int v, val_t x) {
        int ug = hld->group[u];
        int uh = hld->ghead[ug];
        int vg = hld->group[v];
        int vh = hld->ghead[vg];
        if (hld->depth[uh] > hld->depth[vh]) {
            update(v, u, x);
            return;
        }
        if (ug == vg) {
            if (hld->depth[u] > hld->depth[v]) {
                swap(u, v);
            }
            gst[ug].update(hld->gidx[u], hld->gidx[v] + 1, x);
        } else {
            gst[vg].update(1, hld->gidx[v] + 1, x);
            update(u, hld->parent[vh], x);
        }
    }

    val_t query(int u, int v, bool include_top_most = false) {
        int ug = hld->group[u];
        int uh = hld->ghead[ug];
        int vg = hld->group[v];
        int vh = hld->ghead[vg];
        if (hld->depth[uh] > hld->depth[vh]) {
            return query(v, u, include_top_most);
        }
        if (ug == vg) {
            if (hld->depth[u] > hld->depth[v]) {
                swap(u, v);
            }
            return gst[ug].query(hld->gidx[u] + (include_top_most ? 0 : 1), hld->gidx[v] + 1);
        } else {
            val_t res = gst[vg].query(1, hld->gidx[v] + 1);
            return ops.combine(res, query(u, hld->parent[vh], include_top_most));
        }
    }

    HeavyLightDecomposition* hld;
    vector<SegmentTree> gst;
    vector<val_t> val;
    Operators ops;
};
