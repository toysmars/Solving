// acmicpc 11266
//
// 단절점
// graph theory
// articulation point
// cut vertex

#include <bits/stdc++.h>
using namespace std;

class CutVertexSolver {
public:
    vector<vector<int>> g;
    vector<bool> cut;
    vector<int> discoveredAt;
    int d;

    CutVertexSolver(vector<vector<int>>& g) {
        this->g = g;
        this->cut.resize(g.size(), false);
        this->discoveredAt.resize(g.size(), 0);
        this->d = 0;
    }

    void solve(int root) {
        dfs(root, root);
    }

private:
    int dfs(int u, int root) {
        int res = discoveredAt[u] = ++d;
        int children = 0;
        for (int v: g[u]) {
            if (!discoveredAt[v]) {
                children += 1;
                int low = dfs(v, root);
                if (u != root && low >= discoveredAt[u]) {
                    cut[u] = true;
                }
                res = min(res, low);
            } else {
                res = min(res, discoveredAt[v]);
            }
        }
        if (u == root && children > 1) {
            cut[u] = true;
        }
        return res;
    }
};

int main() {
    int V, E;
    scanf("%d%d", &V, &E);
    vector<vector<int>> g(V+1);
    for (int i = 0; i < E; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    CutVertexSolver cutVertexSolver(g);
    for (int u = 1; u <= V; ++u) {
        if (cutVertexSolver.discoveredAt[u] == 0) {
            cutVertexSolver.solve(u);
        }
    }
    vector<int> res;
    for (int u = 1; u <= V; ++u) {
        if (cutVertexSolver.cut[u]) {
            res.push_back(u);
        }
    }
    printf("%lu\n", res.size());
    for (int u: res) {
        printf("%d ", u);
    }
    printf("\n");
    return 0;
}

