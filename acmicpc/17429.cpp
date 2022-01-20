// acmicpc 17429
//
// HLD with subtree query

#include <bits/stdc++.h>
using namespace std;

struct Val {
    uint val;
    uint mul;
    uint add;
};

typedef Val val_t;

struct Operators {
    val_t (*combine)(val_t, val_t);
    val_t (*update)(val_t, val_t);
    val_t (*lazy_update)(val_t, val_t);
    val_t (*repeat)(val_t, int);
};

struct SegmentTree {
    SegmentTree(int n, val_t def_val, Operators ops) : n(n), def_val(def_val), t(4 * n + 1, {0,0,0}), lz(4 * n + 1, {0,1,0}), haslz(4 * n + 1, false), ops(ops) {}

    // update the segment tree with value x for range [ul, ur)
    void Update(int ul, int ur, val_t x) {
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

    val_t Query(int ql, int qr) {
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
            lz[idx] = {0,1,0};
        }
    }

    int n;
    val_t def_val;
    vector<val_t> t;
    vector<val_t> lz;
    vector<bool> haslz;
    Operators ops;
};


// heavy-Light Decomposition solver
// Tree node index must be in range [1, N].
struct HeavyLightDecomposition {

    HeavyLightDecomposition(int n) : n(n), g(n+1), size(n+1), depth(n+1), parent(n+1), group(n+1), dis(n+1), fin(n+1) {}

    void AddEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void Init() {
        group_cnt = 0;
        dis_cnt = 0;
        fill(group.begin(), group.end(), 0);
        ghead.resize(1);
    }

    void Build(int root) {
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
        dis[cur] = ++dis_cnt;
        if (idx == 1) {
            group_cnt += 1;
            ghead.push_back(cur);
        }
        group[cur] = group_cnt;

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
        fin[cur] = dis_cnt;
    }

    int Lca(int u, int v) {
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
    int dis_cnt;
    vector<vector<int>> g;
    vector<int> size;
    vector<int> depth;
    vector<int> parent;
    vector<int> group;
    vector<int> ghead;
    vector<int> dis;
    vector<int> fin;
};

struct HLDQuerier {
    HLDQuerier(HeavyLightDecomposition* hld, val_t def_val, Operators ops): hld(hld), st(hld->n+1, def_val, ops), ops(ops)  {}

    void PathUpdate(int u, int v, val_t x) {
        int ug = hld->group[u];
        int uh = hld->ghead[ug];
        int vg = hld->group[v];
        int vh = hld->ghead[vg];
        if (hld->depth[uh] > hld->depth[vh]) {
            PathUpdate(v, u, x);
            return;
        }
        if (ug == vg) {
            if (hld->depth[u] > hld->depth[v]) {
                swap(u, v);
            }
            st.Update(hld->dis[u], hld->dis[v] + 1, x);
        } else {
            st.Update(hld->dis[vh], hld->dis[v] + 1, x);
            PathUpdate(u, hld->parent[vh], x);
        }
    }

    val_t PathQuery(int u, int v, bool include_top_most = false) {
        int ug = hld->group[u];
        int uh = hld->ghead[ug];
        int vg = hld->group[v];
        int vh = hld->ghead[vg];
        if (hld->depth[uh] > hld->depth[vh]) {
            return PathQuery(v, u, include_top_most);
        }
        if (ug == vg) {
            if (hld->depth[u] > hld->depth[v]) {
                swap(u, v);
            }
            return st.Query(hld->dis[u] + (include_top_most ? 0 : 1), hld->dis[v] + 1);
        } else {
            val_t res = st.Query(hld->dis[vh], hld->dis[v] + 1);
            return ops.combine(res, PathQuery(u, hld->parent[vh], include_top_most));
        }
    }

    void SubTreeUpdate(int r, val_t x) {
        st.Update(hld->dis[r], hld->fin[r] + 1, x);
    }

    val_t SubTreeQuery(int r, bool include_top_most = false) {
        return st.Query(hld->dis[r] + (include_top_most ? 0 : 1), hld->fin[r] + 1);
    }

    HeavyLightDecomposition* hld;
    SegmentTree st;
    Operators ops;
};

Val combine(Val a, Val b) {
    return { a.val + b.val, 0, 0  };
}

Val update(Val a, Val b) {
    return { a.val * b.mul + b.add, 0, 0 };
}

Val lazy_update(Val a, Val b) {
    return { 0, a.mul * b.mul, a.add * b.mul + b.add };
}

Val repeat(Val a, int n) {
    return { 0, a.mul, a.add * n };
}

int main() {
    int N, Q;
    scanf("%d%d", &N, &Q);
    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        hld.AddEdge(u, v);
    }
    hld.Init();
    hld.Build(1);

    HLDQuerier hldq(&hld, {0,1,0}, {combine, update, lazy_update, repeat});
    for (int i = 0; i < Q; ++i) {
        int cmd, x, y;
        uint v;
        scanf("%d", &cmd);
        switch (cmd) {
            case 1:
                scanf("%d%ud", &x, &v);
                hldq.SubTreeUpdate(x, {0, 1, v});
                break;
            case 2:
                scanf("%d%d%ud", &x, &y, &v);
                hldq.PathUpdate(x, y, {0, 1, v});
                break;
            case 3:
                scanf("%d%ud", &x, &v);
                hldq.SubTreeUpdate(x, {0, v, 0});
                break;
            case 4:
                scanf("%d%d%ud", &x, &y, &v);
                hldq.PathUpdate(x, y, {0, v, 0});
                break;
            case 5:
                scanf("%d", &x);
                printf("%u\n", hldq.SubTreeQuery(x, true).val);
                break;
            case 6:
                scanf("%d%d", &x, &y);
                printf("%u\n", hldq.PathQuery(x, y, true).val);
                break;
        }
    }

    return 0;
}
