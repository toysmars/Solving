// max flow
// dinic
// Examples:
//  * https://www.acmicpc.net/problem/1420
//  * https://www.acmicpc.net/problem/2316
//  * https://www.acmicpc.net/problem/2367
//  * https://www.acmicpc.net/problem/11377

#include <bits/stdc++.h>
using namespace std;

typedef int edge_id_t;

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
    MaxFlow(int n) : n(n), flow(0), g(n), level(n), vptr(n) {}

    void addEdge(int u, int v, int cap) {
        edge_id_t uvId = edges.size();
        edges.push_back(Edge(u, v, cap));
        g[u].push_back(uvId);

        edge_id_t vuId = edges.size();
        edges.push_back(Edge(v, u, 0));
        g[v].push_back(vuId);
    }

    int maximumFlow(int source, int sink) {
        while (findAugmentPath(source, sink)) {
            for (int u = 0; u < n; ++u) {
                vptr[u] = g[u].size() - 1;
            }
            int sum = 0;
            while (true) {
                int amount = augment(source, INT_MAX, sink);
                if (amount == 0) break;
                sum += amount;
            }
            if (sum == 0) break;
            flow += sum;
        }
        return flow;
    }

    pair<vector<int>, vector<int>> mincut() {
        pair<vector<int>, vector<int>> ans;
        for (int u = 0; u < n; ++u) {
            if (level[u] == -1) {
                ans.first.push_back(u);
            } else {
                ans.second.push_back(u);
            }
        }
        return ans;
    }

private:
    bool findAugmentPath(int source, int sink) {
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

    int augment(int u, int flow, int sink) {
        if (u == sink) {
            return flow;
        }
        int &j = vptr[u];
        while (j >= 0) {
            int uvIdx = g[u][j];
            Edge& e = edges[uvIdx];
            if (e.residual() > 0 && level[e.v] == level[e.u] - 1) {
                int amount = augment(e.v, min(flow, e.residual()), sink);
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
    int flow;
    vector<vector<edge_id_t>> g;
    vector<int> level;
    vector<int> vptr;
    vector<Edge> edges;
};

