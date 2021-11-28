// General unweighted graph matching

#include <bits/stdc++.h>
using namespace std;

// Find maximum matching on a unweighted undirected graph.
// Implementation based on https://blog.kyouko.moe/20?category=767011
// The vertex number must be in range [1, n].
// O(|V|^3)
struct GraphMatchingSolver {
    GraphMatchingSolver(int n): n(n), bid(0), g(n + 1), visit(n + 1), parent(n + 1), org(n + 1), match(n + 1), aux(n + 1) {}

    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int solve() {
        int ans = 0;
        for(int u = 1; u <= n; u++) {
            if (!match[u]) {
                for (int v: g[u]) {
                    if (!match[v]) {
                        match[u] = v,
                        match[v] = u;
                        ++ans;
                        break;
                    }
                }
            }
        }
        for(int u = 1; u <= n; ++u) {
            if (!match[u] && bfs(u)) {
                ++ans;
            }
        }
        return ans;
    }

    bool bfs(int s) {
        fill(visit.begin(), visit.end(), -1);
        iota(org.begin(), org.end(), 0);
        queue<int> q;
        q.push(s);
        visit[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v: g[u]) {
                if (visit[v] == -1) {
                    parent[v] = u;
                    visit[v] = 1;
                    if (!match[v]) {
                        augment(s, v);
                        return true;
                    }
                    q.push(match[v]);
                    visit[match[v]] = 0;
                } else if (visit[v] == 0 && org[u] != org[v]) {
                    int b = lca(org[u], org[v]);
                    blossom(v, u, b, q);
                    blossom(u, v, b, q);
                }
            }
        }
        return false;
    }

    void augment(int u, int v) {
        int pv, nv;
        do {
            pv = parent[v];
            nv = match[pv];
            match[v] = pv;
            match[pv] = v;
            v = nv;
        } while(u != pv);
    }

    int lca(int u, int v) {
        ++bid;
        while (true) {
            if (u) {
                if (aux[u] == bid) {
                    return u;
                }
                aux[u] = bid;
                u = org[parent[match[u]]];
            }
            swap(u, v);
        }
    }

    void blossom(int u, int v, int b, queue<int>& q) {
        while (org[u] != b) {
            parent[u] = v;
            v = match[u];
            if (visit[v] == 1) {
                q.push(v);
                visit[v] = 0;
            }
            org[u] = org[v] = b;
            u = parent[v];
        }
    }

    int n;
    int bid;
    vector<vector<int>> g;
    vector<int> visit;
    vector<int> parent;
    vector<int> org;
    vector<int> match;
    vector<int> aux;
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    GraphMatchingSolver ms(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        ms.addEdge(u, v);
    }
    printf("%d\n", ms.solve());
    return 0;
}

