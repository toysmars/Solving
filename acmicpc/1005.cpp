// www.acmicpc.net/problem/1005
// * topological sort - bfs
// * critical path
// * Kahn's algorithm

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int main() {
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		int n, k;
		scanf("%d%d", &n, &k);
		vector<int> build(n + 1);
		vector<int> ready(n + 1);
		vector<int> finish(n + 1);
		vector<int> idegree(n + 1);
		vector<vector<int>> graph(n + 1);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &build[i]);
		}
		for (int i = 0; i < k; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			graph[u].push_back(v);
			idegree[v]++;
		}
		queue<int> q;
		for (int i = 1; i <= n; ++i) {
			if (idegree[i] == 0) {
				q.push(i);
			}
		}
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			finish[u] = ready[u] + build[u];
			for (int v : graph[u]) {
				ready[v] = max(ready[v], finish[u]);
				idegree[v]--;
				if (idegree[v] == 0) {
					q.push(v);
				}
			}
		}
		int w;
		scanf("%d", &w);
		printf("%d\n", finish[w]);
	}
	return 0;
}

