// acmicpc 1761
// 
// lowest common ancestor 
// lcm

#include<bits/stdc++.h>
using namespace std;

const int MAX_NODES = 40000;
const int MAX_EXP = 16;

struct Edge {
	Edge(int _u, int _v, int _w): u(_u), v(_v), w(_w) {}
	int u, v, w;
};

int p[MAX_EXP + 1][MAX_NODES + 1];
int l[MAX_EXP + 1][MAX_NODES + 1];
int d[MAX_NODES + 1];
bool visited[MAX_NODES + 1];
vector<vector<Edge>> es;

void dfs(int u, int parent, int w, int depth) {
	if (visited[u]) return;
	visited[u] = true;
	d[u] = depth;
	p[0][u] = parent;
    l[0][u] = w;
	for (auto e: es[u]) {
		if (e.u != u) continue;
		dfs(e.v, e.u, e.w, depth + 1);
	}
}

int lca(int u, int v) {
	if (d[u] > d[v]) {
		return lca(v, u);
	}
	for (int k = MAX_EXP; k >= 0; --k) {
		if (d[v] - d[u] >= (1 << k)) {
			v = p[k][v];
		}
	}
	if (u == v) {
		return u;
	}
	for (int k = MAX_EXP; k >= 0; --k) {
		if (p[k][u] != p[k][v]) {
			u = p[k][u];
			v = p[k][v];
		}
	}
	return p[0][u];
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
	for (int k = 1; k <= MAX_EXP; ++k) {
		for (int u = 1; u <= n; ++u) {
			p[k][u] = p[k-1][p[k-1][u]];
            l[k][u] = l[k-1][p[k-1][u]] + l[k-1][u];
		}
	}
	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
        int a = lca(u, v);
		printf("%d\n", l[MAX_EXP][u] + l[MAX_EXP][v] - 2 * l[MAX_EXP][a]);
	}
	return 0;
}
