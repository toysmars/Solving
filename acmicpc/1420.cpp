// acmicpc 1420
//
// maxflow mincut
// dinic
// min vertex cut

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

char B[101][101];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

int solve(int n, int m) {
    int source = 0;
    int sink = 0;
    MaxFlow mf(2 * n * m);
    auto idx = [=](int y, int x)->int { return 2 * (y * m + x); };
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < m; ++x) {
            if (B[y][x] == '#') continue;
            if (B[y][x] == 'K') source = idx(y, x) + 1;
            if (B[y][x] == 'H') sink = idx(y, x);
            mf.addEdge(idx(y, x), idx(y, x) + 1, 1);
            for (int k = 0; k < 4; ++k) {
                int ny = y + dy[k];
                int nx = x + dx[k];
                if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
                if (B[ny][nx] == '#') continue;
                if (B[y][x] == 'K' && B[ny][nx] == 'H') return -1;
                mf.addEdge(idx(y, x) + 1, idx(ny, nx), 1);
            }
        }
    }
    return mf.maximumFlow(source, sink);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%s", B[i]);
    }
    printf("%d\n", solve(n, m));
    return 0;
}
