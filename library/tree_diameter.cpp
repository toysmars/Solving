// diameter of tree
// radius of tree
// 트리의 지름
//
// Examples
// * https://www.acmicpc.net/problem/1167
// * https://www.acmicpc.net/problem/8872

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v;
    int w;
};

struct TreeDiameter {
    int tree_id;
    int diameter;
    int du;
    int dv;
    int center;
    int radius;
};

struct TreeDiameterSolver {
    TreeDiameterSolver(int n) : n(n), g(n), vis(n), parent(n), bw(n) {}

    void AddEdge(int u, int v, int w) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    // Solves the diameter and radius of trees in the given forest.
    void Solve() {
        fill(parent.begin(), parent.end(), -1);
        for (int s = 0; s < n; ++s) {
            if (parent[s] == -1) {
                auto [du, dv, diameter] = solve_diameter(s);
                auto [center, radius] = solve_radius(dv, diameter);
                trees.push_back(TreeDiameter{
                    .tree_id = (int)trees.size(),
                    .diameter = diameter,
                    .du = du,
                    .dv = dv,
                    .center = center,
                    .radius = radius
                });
            }
        }
    }

    tuple<int, int, int> solve_diameter(int s) {
        fill(vis.begin(), vis.end(), false);
        int du = dfs(s, s, 0).second;
        fill(vis.begin(), vis.end(), false);
        auto [diameter, dv] = dfs(du, du, 0);
        return tie(du, dv, diameter);
    }

    tuple<int, int> solve_radius(int dv, int diameter) {
        int u = dv;
        int center = u;
        int radius = diameter;
        int r = 0;
        while (u != parent[u]) {
            r += bw[u];
            u = parent[u];
            if (radius > max(r, diameter - r)) {
                center = u;
                radius = max(r, diameter - r);
            }
        }
        return tie(center, radius);
    }

    pair<int, int> dfs(int u, int p, int w) {
        if (vis[u]) {
            return make_pair(-1, -1);
        }
        vis[u] = true;
        parent[u] = p;
        bw[u] = w;
        int max_dist = 0;
        int max_v = u;
        for (auto e: g[u]) {
            if (vis[e.v]) continue;
            auto res = dfs(e.v, u, e.w);
            if (max_dist < res.first + e.w) {
                max_dist = res.first + e.w;
                max_v = res.second;
            }
        }
        return make_pair(max_dist, max_v);
    }

    int n;
    vector<vector<Edge>> g;
    vector<bool> vis;
    vector<int> parent;
    vector<int> bw;

    vector<TreeDiameter> trees;
};
