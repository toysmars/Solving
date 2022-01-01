// Dijkstra
// Single source shortest path
// 
// Examples:
// * https://www.acmicpc.net/problem/11779

#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;

struct Edge {
    int v;
    int w;
};

struct Dijkstra {
    Dijkstra(int n): g(n), p(n) {}

    void AddEdge(int u, int v, int w) {
        g[u].push_back({v, w});
    }

    vector<int> Solve(int s) {
        vector<int> dist(g.size(), INF);
        priority_queue<pair<pair<int, int>, int>> pq;
        pq.emplace(make_pair(0, s), -1);
        while (!pq.empty()) {
            auto [here, from] = pq.top();
            auto [d, u] = here;
            d = -d;
            pq.pop();
            if (dist[u] <= d) continue;
            dist[u] = d;
            p[u] = from;
            for (const Edge& e : g[u]) {
                if (dist[e.v] > d + e.w) {
                    pq.emplace(make_pair(-(d + e.w), e.v), u);
                }
            }
        }
        return dist;
    }

    vector<int> Path(int e) {
        vector<int> ans;
        ans.push_back(e);
        while (p[e] != -1) {
            e = p[e];
            ans.push_back(e);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

    vector<vector<Edge>> g;
    vector<int> p;
};
