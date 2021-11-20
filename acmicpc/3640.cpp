// acmicpc 3640
//
// mcmf
// min cost max flow
// shortest faster algorithm

#include <bits/stdc++.h>
using namespace std;

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
    MinCostMaxFlow(size_t n) : g(n), n(n) {}

    void addEdge(int u, int v, cap_t cap, cost_t cost) {
        if (u != v) {
            g[u].emplace_back(Edge(u, v, cap, cost, g[v].size()));
            g[v].emplace_back(Edge(v, u, 0, -cost, g[u].size() - 1));
        }
    }

    pair<cap_t, cost_t> augment(int s, int e, cap_t augment_limit) {
        vector<cost_t> dist(n, INF_COST);
        vector<int> count(n);
        vector<bool> in_queue(n);
        vector<cap_t> amount(n);
        vector<int> from(n, -1);
        queue<int> q;

        // SPFA
        q.push(s);
        in_queue[s] = true;
        dist[s] = 0;
        amount[s] = INF_CAP;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            in_queue[u] = false;
            if (++count[u] >= n) {
                // found negative cycle
                return make_pair(0, 0);
            }
            for (const auto& e : g[u]) {
                if (isCapacityPositive(e.res_cap) > 0 && dist[e.v] > dist[u] + e.cost) {
                    dist[e.v] = dist[u] + e.cost;
                    amount[e.v] = min(amount[u], e.res_cap);
                    from[e.v] = e.dual_id;
                    if (!in_queue[e.v]) {
                        q.push(e.v);
                        in_queue[e.v] = true;
                    }
                }
            }
        }

        auto flow_augment = amount[e];
        auto cost_augment = dist[e];

        if (!isCapacityPositive(flow_augment) || (augment_limit <= 0 && cost_augment >= 0)) {
            return make_pair(0, 0);
        }
        if (augment_limit > 0) {
            flow_augment = min(flow_augment, augment_limit);
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

    pair<cap_t, cost_t> solve(int s, int e, cap_t flow_limit = INF_CAP) {
        cap_t total_flow = 0;
        cost_t total_cost = 0;
        while (true) {
            auto res = augment(s, e, flow_limit - total_flow);
            if (res.first <= 0) break;
            total_flow += res.first;
            total_cost += res.second;
        }
        return make_pair(total_flow, total_cost);
    }

  private:
    int n;
    Graph g; // graph
};

int main() {
    int V, E;
    while (scanf("%d%d", &V, &E) > 0) {
        MinCostMaxFlow mcmf(2 * (V + 1));
        for (int i = 1; i <= V; ++i) {
            mcmf.addEdge(2 * i, 2 * i + 1, 1, 0);
        }
        for (int i = 0; i < E; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            mcmf.addEdge(2 * u + 1, 2 * v, 1, w);
        }
        printf("%d\n", mcmf.solve(3, 2*V, 2).second);
    }
    return 0;
};
