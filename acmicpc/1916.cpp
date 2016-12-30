// www.acmicpc.net/problem/1916
// * shortest path
// * dijkstra
#include <cstdio>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

const int INF = INT_MAX;

struct Edge {
	Edge(int u, int v, int w) : u(u), v(v), w(w) {}
	int u;
	int v;
	int w;
};

typedef vector<vector<Edge>> Graph;

vector<int> dijkstra(Graph& g, int s) {
	vector<int> dist(g.size(), INF);
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, s));
	while (!pq.empty()) {
		int u = pq.top().second;
		int d = -pq.top().first;
		pq.pop();
		if (dist[u] <= d) continue;
		dist[u] = d;
		for (const Edge& e : g[u]) {
			if (dist[e.v] > d + e.w) {
				pq.push(make_pair(-(d + e.w), e.v));
			}
		}
	}
	return dist;
}

int main() {
	int vs, es;
	scanf("%d%d", &vs, &es);
	Graph g(vs + 1);
	for (int ei = 0; ei < es; ++ei) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		g[u].push_back(Edge(u, v, w));
	}
	int s, e;
	scanf("%d%d", &s, &e);
	auto res = dijkstra(g, s);
	printf("%d\n", res[e]);

	return 0;
}

