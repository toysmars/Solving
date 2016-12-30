// www.acmicpc.net/problem/1922
// * mst
// * minimum spanning tree
// * kruskal
// * disjoint set
// * union find

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

class DisjointSet {
public:
	DisjointSet(int size) : p(size), r(size) {
		for (int i = 0; i < size; ++i) p[i] = i;
	}

	int find(int x) {
		if (p[x] != x) p[x] = find(p[x]);
		return p[x];
	}

	void join(int x, int y) {
		int xp = find(x);
		int yp = find(y);
		if (xp != yp) {
			if (r[xp] < r[yp]) p[xp] = yp;
			else if (r[xp] > r[yp]) p[yp] = xp;
			else { p[yp] = xp; r[xp]++; }
		}
	}

	vector<int> p;
	vector<int> r;
};

struct Edge {
	Edge(int u, int v, int w) : u(u), v(v), w(w) {}
	int u;
	int v;
	int w;
	bool operator<(const Edge& rhs) const {
		return w < rhs.w;
	}
};

vector<Edge> kruskal(int nv, vector<Edge> edges) {
	vector<Edge> res;
	DisjointSet ds(nv);
	sort(edges.begin(), edges.end());
	for (const Edge& e : edges) {
		if (ds.find(e.u) != ds.find(e.v)) {
			ds.join(e.u, e.v);
			res.push_back(e);
		}
	}
	return res;
}

int main() {
	int nv, ne;
	scanf("%d%d", &nv, &ne);
	vector<Edge> edges;
	for (int ei = 0; ei < ne; ++ei) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		edges.push_back(Edge(u, v, w));
	}
	vector<Edge> res = kruskal(nv+1, edges);
	int sum = 0;
	for (const Edge& e : res) {
		sum += e.w;
	}
	printf("%d\n", sum);
	return 0;
}

