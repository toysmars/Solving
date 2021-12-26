// Tree
// Centroid Decomposition
//
// Examples
// https://www.acmicpc.net/problem/5820

#include <bits/stdc++.h>
using namespace std;

struct CentroidDecomposition {
    CentroidDecomposition(int n): n(n), g(n), g_prime(n), solved(n), root(0), sz(n) {}

    void AddEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // Solves the given tree and builds centroid tree.
    void Solve() {
        root = solve(0);
    }

    vector<vector<int>>& CentroidG() { return g_prime; }
    int Root() { return root; }

    int solve(int u) {
        countSize(u, -1);
        int c = findCentroid(u, -1, sz[u]);
        solved[c] = true;
        for (auto v: g[c]) {
            if (solved[v]) continue;
            int nc = solve(v);
            g_prime[c].push_back(nc);
        }
        return c;
    }

    int countSize(int u, int p) {
        sz[u] = 1;
        for (auto v: g[u]) {
            if (v == p || solved[v]) continue;
            sz[u] += countSize(v, u);
        }
        return sz[u];
    }

    int findCentroid(int u, int p, int tree_size) {
        for (auto v: g[u]) {
            if (v == p || solved[v]) continue;
            if (2 * sz[v] > tree_size) {
                return findCentroid(v, u, tree_size);
            }
        }
        return u;
    }

    int n;
    vector<vector<int>> g;
    vector<vector<int>> g_prime;
    vector<bool> solved;
    int root;
    vector<int> sz;
};
