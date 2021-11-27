// General unweighted graph matching

#include <bits/stdc++.h>
using namespace std;

// Find maximum matching on a unweighted undirected graph.
// Implementation based on https://blog.kyouko.moe/20?category=767011
// O(|V|^3)
struct GraphMatchingSolver {
    GraphMatchingSolver(int n): n(n), it(0), g(n), visit(n), parent(n), org(n), match(n), aux(n) {}

    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int solve() {
        int ans = 0;
        vector<int> v(n - 1);
        // random initialization
        iota(v.begin(), v.end(), 0);
        shuffle(v.begin(), v.end(), mt19937(0x94949));
        for (auto x: v) {
            if (!match[x]) {
                for (auto y: g[x]) {
                    if (!match[y]) {
                        match[x] = y,
                        match[y] = x;
                        ++ans;
                        break;
                    }
                }
            }
        }
        for(int i = 0; i < n; ++i) {
            if (!match[i] && bfs(i)) {
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
                } else if(visit[v] == 0 && org[u] != org[v]) {
                    int a = lca(org[u], org[v]);
                    blossom(v, u, a, q);
                    blossom(u, v, a, q);
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
        ++it;
        while (true) {
            if (u) {
                if (aux[u] == it) {
                    return u;
                }
                aux[u] = it;
                v = org[parent[match[u]]];
            }
            swap(u, v);
        }
    }

    void blossom(int u, int v, int a, queue<int>& q) {
        while (org[u] != a) {
            parent[u] = v;
            v = match[u];
            if (visit[v] == 1) {
                q.push(v);
                visit[v] = 0;
            }
            org[u] = org[v] = a;
            u = parent[v];
        }
    }

    int n;
    int it;
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
    GraphMatchingSolver ms(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        ms.addEdge(u, v);
    }
    printf("%d\n", ms.solve());
    return 0;
}
