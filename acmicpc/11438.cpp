// acmicpc 11438

// lcm
// lowest common ancestor

#include<bits/stdc++.h>
using namespace std;

const int MAX_NODES = 100000;
const int MAX_EXP = 17;

class LowestCommonAncestor {
  public:
    LowestCommonAncestor(int V) {
        _n = V;
        _exp = 0;
        while (V > 0) {
            _exp += 1;
            V >>= 1;
        }
        _g.resize(_n + 1);
        _p.resize(_exp + 1);
        for (int i = 0; i <= _exp; ++i) {
            _p[i].resize(_n + 1);
        }
        _d.resize(_n + 1);
        _v.resize(_n + 1);
    }

    void addEdge(int u, int v) {
        _g[u].push_back(v);
        _g[v].push_back(u);
    }

    void solve() {
        dfs(1, 0, 0);
        for (int k = 1; k <= _exp; ++k) {
            for (int u = 1; u <= _n; ++u) {
                _p[k][u] = _p[k-1][_p[k-1][u]];
            }
        }
    }

    int lca(int u, int v) {
        if (_d[u] > _d[v]) {
            return lca(v, u);
        }
        for (int k = _exp; k >= 0; --k) {
            if (_d[v] - _d[u] >= (1 << k)) {
                v = _p[k][v];
            }
        }
        if (u == v) {
            return u;
        }
        for (int k = _exp; k >= 0; --k) {
            if (_p[k][u] != _p[k][v]) {
                u = _p[k][u];
                v = _p[k][v];
            }
        }
        return _p[0][u];
    }

  private:
    void dfs(int u, int parent, int depth) {
        if (_v[u]) return;
        _v[u] = true;
        _d[u] = depth;
        _p[0][u] = parent;
        for (int v: _g[u]) {
            dfs(v, u, depth + 1);
        }
    }

  private:
    vector<vector<int>> _g;
    vector<vector<int>> _p;
    vector<int> _d;
    vector<bool> _v;
    int _n;
    int _exp;
};

int main() {
	int n;
	scanf("%d", &n);
    LowestCommonAncestor lca(n);
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
        lca.addEdge(u, v);
	}
    lca.solve();
	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%d\n", lca.lca(u,v));
	}
	return 0;
}
