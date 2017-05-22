// https://www.hackerrank.com/contests/w32/challenges/balls-and-boxes
// * minimum cost maximum flow
// * maxflow
// * mcmf
// * spfa

#include <cstdio>
#include <cstdlib>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 1000000000

int N, M;
int A[101];
int C[101];
int B[101][101];

int V, V1, V2, V3;
typedef int cap_t;
typedef int cost_t;

const int INF_CAP = numeric_limits<cap_t>::max() / 2;
const int INF_COST = numeric_limits<cost_t>::max() / 2;

bool isCapacityPositive(cap_t cap) {
    return cap > 0;
}

class Edge {
  public:
    Edge() : u(0), v(0), cost(0), res_cap(0), org_cap(0), dual_id(0) {}
    Edge(int u, int v, cap_t cap, cost_t cost, size_t id) : u(u), v(v), res_cap(cap), org_cap(cap), cost(cost), dual_id(id) {}

    int u;
    int v;
    cost_t cost;
    cap_t res_cap;
    cap_t org_cap;
    size_t dual_id;
};

typedef vector<vector<Edge>> Graph;

// Minimum Cost Maximum Flow
// precondition: no negative cycle.
// mcmf.solve(source, sink); // min cost max flow
// mcmf.solve(source, sink, 0); // min cost flow
// mcmf.solve(source, sink, goal_flow); // min cost flow with total_flow >= goal_flow if possible
class MinCostMaxFlow {
  public:
    MinCostMaxFlow(size_t n) : g(n), n(n), pi(n), need_normalize(false), augmented(false), last_start(-1) {}

    void addEdge(int u, int v, cap_t cap, cost_t cost) {
        if (u != v) {
            g[u].emplace_back(Edge(u, v, cap, cost, g[v].size()));
            g[v].emplace_back(Edge(v, u, 0, -cost, g[u].size() - 1));
            if (cost < 0 || augmented) {
                need_normalize = true;
            }
        }
    }

    bool normalize(int s) {
        vector<cost_t> dist(n, INF_COST);
        vector<int> count(n);
        vector<bool> in_queue(n);
        queue<int> q;

        // SPFA
        q.push(s);
        in_queue[s] = true;
        dist[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            in_queue[u] = false;
            if (++count[u] >= n) {
                // found negative cycle
                return false;
            }
            for (const auto& e : g[u]) {
                if (isCapacityPositive(e.res_cap) > 0 && dist[e.v] > dist[u] + e.cost) {
                    dist[e.v] = dist[u] + e.cost;
                    if (!in_queue[e.v]) {
                        q.push(e.v);
                        in_queue[e.v] = true;
                    }
                }
            }
        }
        // potential
        for (int u = 0; u < n; ++u) {
            pi[u] = dist[u];
        }
        need_normalize = false;
        return true;
    }

    pair<cap_t, cost_t> augment(int s, int e, cap_t augment_limit) {
        priority_queue<pair<cost_t, int>> pq;
        vector<cost_t> dist(n, INF_COST);
        vector<cap_t> amount(n);
        vector<int> from(n, -1);
        vector<bool> visit(n);

        if (need_normalize || (augmented && last_start != s)) {
            normalize(s);
        }
        augmented = true;
        last_start = s;

        // find shortest path with dijkstra
        pq.emplace(0, s);
        dist[s] = 0;
        amount[s] = INF_CAP;
        while (!pq.empty()) {
            int d = -pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if (visit[u] || u == e) {
                continue;
            }
            visit[u] = true;
            for (const auto& e : g[u]) {
                if (!visit[e.v] && isCapacityPositive(e.res_cap)) {
                    auto vd = d + e.cost - pi[e.v] + pi[u];
                    if (dist[e.v] > vd) {
                        dist[e.v] = vd;
                        amount[e.v] = min(amount[u], e.res_cap);
                        from[e.v] = e.dual_id;
                        pq.emplace(-vd, e.v);
                    }
                }
            }
        }
        auto flow_augment = amount[e];
        auto cost_augment = dist[e] + pi[e] - pi[s];

        if (!isCapacityPositive(flow_augment) || (augment_limit <= 0 && cost_augment >= 0)) {
            return make_pair(0, 0);
        }
        if (augment_limit > 0) {
            flow_augment = min(flow_augment, augment_limit);
        }
        // upate potential
        for (int u = 0; u < n; ++u) {
            if (isCapacityPositive(amount[u])) {
                pi[u] += dist[u];
            }
        }
        // augment flow
        auto p = e;
        while (from[p] != -1) {
            int vu_id = from[p];
            int uv_id = g[p][vu_id].dual_id;
            int u = g[p][vu_id].v;
            int v = p;
            g[u][uv_id].res_cap -= flow_augment;
            g[v][vu_id].res_cap += flow_augment;
            p = u;
        }
        return make_pair(flow_augment, cost_augment * flow_augment);
    }

    pair<cap_t, cost_t> solve(int s, int e, cap_t flow_goal = INF_CAP) {
        cap_t total_flow = 0;
        cost_t total_cost = 0;
        while (true) {
            auto res = augment(s, e, flow_goal - total_flow);
            if (res.first <= 0) break;
            total_flow += res.first;
            total_cost += res.second;
        }
        return make_pair(total_flow, total_cost);
    }

  private:
    int n;
    Graph g; // graph
    vector<cost_t> pi; // potential
    bool need_normalize;
    bool augmented;
    int last_start;
};

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &A[i]);
    }
    for (int j = 0; j < M; ++j) {
        scanf("%d", &C[j]);
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            scanf("%d", &B[i][j]);
        }
    }
    V1 = N;
    V2 = M;
    V3 = N + 1;
    V = V1 + V2 + V3;
    int source = V;
    int sink = V + 1;

    MinCostMaxFlow mcmf(V + 2);
    for (int i = 0; i < N; ++i) {
        mcmf.addEdge(source, i, A[i], 0);
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            mcmf.addEdge(i, V1 + j, 1, -B[i][j]);
        }
    }
    for (int j = 0; j < M; ++j) {
        if (C[j] > 0) {
            mcmf.addEdge(V1 + j, V1 + V2, C[j], 0);
        }
        for (int k = C[j], p = 1; k < N; ++k, p++) {
            mcmf.addEdge(V1 + j, V1 + V2 + p, 1, 0);
        }
    }
    mcmf.addEdge(V1 + V2, sink, INF, 0);
    for (int k = 1, p = 1; k <= N; ++k, p += 2) {
        mcmf.addEdge(V1 + V2 + k, sink, INF, p);
    }
    
    auto res = mcmf.solve(source, sink, 0);
    printf("%d\n", -res.second);
    return 0;
}
