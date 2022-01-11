// LCA
// Lowest common ancestor
//
// Examples:
// * https://www.acmicpc.net/problem/1761
// * https://www.acmicpc.net/problem/7527
// * https://www.acmicpc.net/problem/11438
// * https://www.acmicpc.net/problem/15480
// * https://www.acmicpc.net/problem/17399

#include<bits/stdc++.h>
using namespace std;

struct LowestCommonAncestorSolver {
    LowestCommonAncestorSolver(int n) : n(n), exp(0), g(n+1), d(n+1), v(n+1) {
        int tn = n;
        while (tn > 0) {
            exp += 1;
            tn >>= 1;
        }
        p.resize(exp + 1);
        for (int i = 0; i <= exp; ++i) {
            p[i].resize(n + 1);
        }
    }

    void AddEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void Build() {
        dfs(1, 0, 0);
        for (int k = 1; k <= exp; ++k) {
            for (int u = 1; u <= n; ++u) {
                p[k][u] = p[k-1][p[k-1][u]];
            }
        }
    }

    int Lca(int u, int v) {
        if (d[u] > d[v]) {
            return Lca(v, u);
        }
        for (int k = exp; k >= 0; --k) {
            if (d[v] - d[u] >= (1 << k)) {
                v = p[k][v];
            }
        }
        if (u == v) {
            return u;
        }
        for (int k = exp; k >= 0; --k) {
            if (p[k][u] != p[k][v]) {
                u = p[k][u];
                v = p[k][v];
            }
        }
        return p[0][u];
    }

    int Distance(int u, int v) {
        int lca = Lca(u, v);
        if (lca == u) {
            return d[v] - d[u];
        } else if (lca == v) {
            return d[u] - d[v];
        } else {
            return d[u] + d[v] - 2 * d[lca];
        }
    }

    int KthParent(int u, int k) {
        if (d[u] < k) return -1;
        int texp = exp;
        while (k > 0 && texp >= 0) {
            if (k >= (1 << texp)) {
                k -= (1 << texp);
                u = p[texp][u];
            }
            texp--;
        }
        return u;
    }

    void dfs(int u, int parent, int depth) {
        if (v[u]) return;
        v[u] = true;
        d[u] = depth;
        p[0][u] = parent;
        for (int v: g[u]) {
            dfs(v, u, depth + 1);
        }
    }

    int n;
    int exp;
    vector<vector<int>> g;
    vector<int> d;
    vector<bool> v;
    vector<vector<int>> p;
};
