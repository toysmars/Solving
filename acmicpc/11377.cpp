// acmicpc 11377
//
// maxflow
// Dinic's algorithm

#include <bits/stdc++.h>
using namespace std;

typedef int EdgeId;

struct Edge {
    int u;
    int v;
    int cap;
    int flow;

    Edge(int u, int v, int cap) : u(u), v(v), cap(cap), flow(0) {}
    int residual() { return cap - flow; }
};

class MaxFlow {
public:
    MaxFlow(int n, int source, int sink) : n(n), g(n), level(n), vptr(n), source(source), sink(sink), flow(0) {}

    void addEdge(int u, int v, int cap) {
        EdgeId uvId = edges.size();
        edges.push_back(Edge(u, v, cap));
        g[u].push_back(uvId);

        EdgeId vuId = edges.size();
        edges.push_back(Edge(v, u, 0));
        g[v].push_back(vuId);
    }

    int maximumFlow() {
        while (findAugmentPath()) {
            for (int u = 0; u < n; ++u) {
                vptr[u] = g[u].size() - 1;
            }
            int sum = 0;
            while (true) {
                int amount = augment(source, INT_MAX);
                if (amount == 0) break;
                sum += amount;
            }
            if (sum == 0) break;
            flow += sum;
        }
        return flow;
    }

private:
    bool findAugmentPath() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(sink);
        level[sink] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto edgeId : g[u]) {
                Edge& e = edges[edgeId];
                Edge& re = edges[edgeId ^ 1];
                if (re.residual() > 0 && level[e.v] == -1) {
                    level[e.v] = level[e.u] + 1;
                    if (e.v == source) {
                        return true;
                    }
                    q.push(e.v);
                }
            }
        }
        return false;
    }

    int augment(int u, int flow) {
        if (u == sink) {
            return flow;
        }
        int &j = vptr[u];
        while (j >= 0) {
            int uvIdx = g[u][j];
            Edge& e = edges[uvIdx];
            if (e.residual() > 0 && level[e.v] == level[e.u] - 1) {
                int amount = augment(e.v, min(flow, e.residual()));
                if (amount > 0) {
                    edges[uvIdx].flow += amount;
                    edges[uvIdx^1].flow -= amount;
                    return amount;
                }
            }
            j -= 1;
        }
        return 0;
    }

  private:
    int n;
    int source;
    int sink;
    int flow;
    vector<vector<EdgeId>> g;
    vector<bool> visit;
    vector<Edge> edges;
    vector<int> level;
    vector<int> vptr;
};

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int source = n + m;
    int additional = n + m + 1;
    int sink = n + m + 2;
    MaxFlow mf(n + m + 3, source, sink);

    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        for (int j = 0; j < x; ++j) {
            int y;
            scanf("%d", &y);
            mf.addEdge(i, n + y - 1, 1);
        }
    }
    mf.addEdge(source, additional, k);
    for (int i = 0; i < n; ++i) {
        mf.addEdge(source, i, 1);
        mf.addEdge(additional, i, 1);
    }
    for (int i = 0; i < m; ++i) {
        mf.addEdge(n + i, sink, 1);
    }
    printf("%d\n", mf.maximumFlow());
    return 0;
}
