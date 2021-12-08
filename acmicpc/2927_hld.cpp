#include <bits/stdc++.h>
using namespace std;

typedef int val_t;

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

    static val_t min(val_t a, val_t b) { return a < b ? a : b; }
    static val_t max(val_t a, val_t b) { return a > b ? a : b; }
    static val_t sum(val_t a, val_t b) { return a + b; }
    static val_t assign(val_t a, val_t b) { return b; }

    int n;
    val_t def_val;
    vector<val_t> t;
    Operations ops;
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
    HLDQuerier(HeavyLightDecomposition* hld, val_t init_val, val_t def_val, Operations ops): hld(hld), val(hld->n+1), gst(), ops(ops) {
        gst.push_back(SegmentTree(0, def_val, ops));
        for (int gid = 1; gid <= hld->group_cnt; ++gid) {
            gst.push_back(SegmentTree(hld->gsize[gid], def_val, ops));
        }
    }

    void update(int u, val_t x) {
        int ug = hld->group[u];
        gst[ug].update(hld->gidx[u], x);
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
    Operations ops;
};

struct DisjointSet {
    DisjointSet(int n) {
        for (int i = 0; i < n; ++i) {
            s.push_back(i);
            r.push_back(0);
        }
    }
    int find(int x) {
        if (s[x] != x) {
            s[x] = find(s[x]);
        }
        return s[x];
    }
    void join(int x, int y) {
        int sx = find(x);
        int sy = find(y);
        if (sx == sy) {
            return;
        }
        if (r[sx] < r[sy]) {
            swap(sx, sy);
        }
        s[sy] = sx;
        if (r[sx] == r[sy]) {
            r[sx] += 1;
        }
    }
    vector<int> s;
    vector<int> r;
};

int main() {
    int n;
    scanf("%d", &n);
    vector<int> peng(n + 1);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &peng[i]);
    }
    int q;
    scanf("%d", &q);
    vector<pair<char, pair<int ,int>>> qs(q);
    for (int i = 0; i < q; ++i) {
        char cmd[20];
        int a, b;
        scanf("%s%d%d", cmd, &a, &b);
        qs[i] = make_pair(cmd[0], make_pair(a, b));
    }

    DisjointSet ds(n + 1);
    HeavyLightDecomposition hld(n);
    hld.init();
    vector<string> res(q);
    for (int i = 0; i < q; ++i) {
        char cmd = qs[i].first;
        int a = qs[i].second.first;
        int b = qs[i].second.second;
        if (cmd == 'e') {
            if (ds.find(a) != ds.find(b)) {
                res[i] = "impossible";
            }
        }
        if (cmd == 'b') {
            if (ds.find(a) != ds.find(b)) {
                ds.join(a, b);
                hld.addEdge(a, b);
                res[i] = "yes";
            } else {
                res[i] = "no";
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (ds.find(i) == i) {
            hld.build(i);
        }
    }

    HLDQuerier hldq(&hld, 0, 0, {SegmentTree::sum, SegmentTree::assign});
    for (int i = 1; i <= n; ++i) {
        hldq.update(i, peng[i]);
    }
    for (int i = 0; i < q; ++i) {
        char cmd = qs[i].first;
        int a = qs[i].second.first;
        int b = qs[i].second.second;
        if (cmd == 'e' && res[i] == "") {
            res[i] = std::to_string(hldq.query(a, b, true));
        }
        if (cmd == 'p') {
            hldq.update(a, b);
        }
    }
    for (auto r: res) {
        if (r == "") continue;
        printf("%s\n", r.c_str());
    }

    return 0;
}
