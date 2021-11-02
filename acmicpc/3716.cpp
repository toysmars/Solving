// #3716
// tree 
// lca 
// lowest common ancestor

#include<bits/stdc++.h>
using namespace std;

struct Edge {
	Edge(int _u, int _v, int _w): u(_u), v(_v), w(_w) {}
	int u, v, w;
};

int p[21][100001];
int pmin[21][100001];
int pmax[21][100001];
int d[100001];
bool visited[100001];
vector<vector<Edge>> es;

void dfs(int u, int parent, int w, int depth) {
	if (visited[u]) return;
	visited[u] = true;
	d[u] = depth;
	p[0][u] = parent;
	pmin[0][u] = w;
	pmax[0][u] = w;
	for (auto e: es[u]) {
		if (e.u != u) continue;
		dfs(e.v, e.u, e.w, depth + 1);
	}
}

pair<int, int> solve(int u, int v) {
	if (d[u] > d[v]) {
		return solve(v, u);
	}
	int rmin = 1000000;
	int rmax = 0;
	for (int k = 20; k >= 0; --k) {
		if (d[v] - d[u] >= (1 << k)) {
			rmin = min(rmin, pmin[k][v]);
			rmax = max(rmax, pmax[k][v]);
			v = p[k][v];
		}
	}
	if (u == v) {
		return make_pair(rmin, rmax);
	}
	for (int k = 20; k >= 0; --k) {
		if (p[k][u] != p[k][v]) {
			rmin = min({rmin, pmin[k][u], pmin[k][v]});
			rmax = max({rmax, pmax[k][u], pmax[k][v]});
			u = p[k][u];
			v = p[k][v];
		}
	}
	rmin = min({rmin, pmin[0][u], pmin[0][v]});
	rmax = max({rmax, pmax[0][u], pmax[0][v]});
	return make_pair(rmin, rmax);
}

int main() {
	int n;
	scanf("%d", &n);
	es.resize(n + 1);
	for (int i = 0; i < n - 1; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		es[u].push_back(Edge(u, v, w));
		es[v].push_back(Edge(v, u, w));
	}
	dfs(1, 0, 0, 0);
	for (int k = 1; k <= 20; ++k) {
		for (int u = 1; u <= n; ++u) {
			p[k][u] = p[k-1][p[k-1][u]];
			pmin[k][u] = min(pmin[k-1][p[k-1][u]], pmin[k-1][u]);
			pmax[k][u] = max(pmax[k-1][p[k-1][u]], pmax[k-1][u]);
		}
	}
	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		auto res = solve(u, v);
		printf("%d %d\n", res.first, res.second);
	}
	return 0;
}
