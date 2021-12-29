// Bellman-Ford
// Shortest Path
// Negative cycle detection
//
// Examples:
// https://www.acmicpc.net/problem/1865

#include <bits/stdc++.h>
using namespace std;

const int INF = (int)1e9;
const int NINF = (int)-1e9;

struct Edge {
    int v;
    int w;
};

struct BellmanFord {
    BellmanFord(int n): n(n), g(n) {}

    void AddEdge(int u, int v, int w) {
        g[u].push_back({v, w});
    }

    // Finds shortest paths from starting vertes `s`.
    // It sets `NINF` on a vertes in dist array when a negative-wighted cycle is detected to the vertex.
    vector<int> Solve(int s) {
        vector<int> d(n, INF);
        d[s] = 0;
        for (int i = 1; i < n; ++i) {
            for (int u = 0; u < n; ++u) {
                if (d[u] == INF) continue;
                for (auto e: g[u]) {
                    if (d[e.v] > d[u] + e.w) {
                        d[e.v] = d[u] + e.w;
                    }
                }
            }
        }
        for (int u = 0; u < n; ++u) {
            if (d[u] == INF) continue;
            for (auto e: g[u]) {
                if (d[e.v] > d[u] + e.w) {
                    d[e.v] = NINF;
                }
            }
        }
        return d;
    }

    int n;
    vector<vector<Edge>> g;
};
