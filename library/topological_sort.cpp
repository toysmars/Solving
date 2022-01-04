// Topological sort
// 위상정렬
//
// Examples:
// https://www.acmicpc.net/problem/2252
// https://www.acmicpc.net/problem/2623

#include <bits/stdc++.h>
using namespace std;

struct TopologicalSort {
    TopologicalSort(int n): g(n), d(n), f(n) {}

    void AddEdge(int u, int v) {
        g[u].push_back(v);
    }

    // Solves topological sort problem.
    // Returns true when the given graph is a DAG.
    // Returns false when a cycle is detected.
    bool Solve() {
        for (int u = 0; u < g.size(); ++u) {
            if (!d[u]) {
                if (!dfs(u)) return false;
            }
        }
        reverse(order.begin(), order.end());
        return true;
    }

    bool dfs(int u) {
        if (f[u]) return true;
        if (d[u]) return false;

        d[u] = true;
        for (int v: g[u]) {
            if (!dfs(v)) return false;
        }
        f[u] = true;
        order.push_back(u);
        return true;
    }

    vector<vector<int>> g;
    vector<bool> d;
    vector<bool> f;
    vector<int> order;
};
