// acmicpc 11400
//
// graph theory
// bridges
// cut edge
// 단절선

#include <bits/stdc++.h>
using namespace std;


class CutEdgeSolver {
public:
    vector<vector<int>> g;
    vector<pair<int, int>> cuts;
    vector<int> discoveredAt;
    int d;

    CutEdgeSolver(vector<vector<int>>& g) {
        this->g = g;
        this->discoveredAt.resize(g.size(), 0);
        this->d = 0;
    }

    void solve(int root) {
        dfs(root, -1);
    }

private:
    int dfs(int u, int parent) {
        int res = discoveredAt[u] = ++d;
        for (int v: g[u]) {
            if (v == parent) {
                continue;
            }
            if (!discoveredAt[v]) {
                int low = dfs(v, u);
                if (low > discoveredAt[u]) {
                    cuts.emplace_back(min(u, v), max(u, v));
                }
                res = min(res, low);
            } else {
                res = min(res, discoveredAt[v]);
            }
        }
        return res;
    }
};

int main() {
    int V, E;
    scanf("%d%d", &V, &E);
    vector<vector<int>> g(V + 1);
    for (int i = 0; i < E; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    CutEdgeSolver cutEdgeSolver(g);
    for (int u = 1; u <= V; ++u) {
        if (cutEdgeSolver.discoveredAt[u] == 0) {
            cutEdgeSolver.solve(u);
        }
    }
    auto cuts = cutEdgeSolver.cuts;
    sort(cuts.begin(), cuts.end());
    printf("%lu\n", cuts.size());
    for (auto e: cuts) {
        printf("%d %d\n", e.first, e.second);
    }
    return 0;
}
