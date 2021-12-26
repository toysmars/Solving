// acmicpc 5820
//
// Tree,
// Centroid Decomposition
// Finding a path in a tree with length K.

#include <bits/stdc++.h>
using namespace std;

struct CentroidDecomposition {
    CentroidDecomposition(int n): n(n), g(n), g_prime(n), solved(n), root(0), sz(n) {}

    void AddEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // Solves the given tree and builds centroid tree.
    void Solve() {
        root = solve(0);
    }

    vector<vector<int>>& CentroidG() { return g_prime; }
    int Root() { return root; }

    int solve(int u) {
        countSize(u, -1);
        int c = findCentroid(u, -1, sz[u]);
        solved[c] = true;
        for (auto v: g[c]) {
            if (solved[v]) continue;
            int nc = solve(v);
            g_prime[c].push_back(nc);
        }
        return c;
    }

    int countSize(int u, int p) {
        sz[u] = 1;
        for (auto v: g[u]) {
            if (v == p || solved[v]) continue;
            sz[u] += countSize(v, u);
        }
        return sz[u];
    }

    int findCentroid(int u, int p, int tree_size) {
        for (auto v: g[u]) {
            if (v == p || solved[v]) continue;
            if (2 * sz[v] > tree_size) {
                return findCentroid(v, u, tree_size);
            }
        }
        return u;
    }

    int n;
    vector<vector<int>> g;
    vector<vector<int>> g_prime;
    vector<bool> solved;
    int root;
    vector<int> sz;
};

struct Edge {
    int v;
    int w;
};

const int MAX_N = 200000;
const int MAX_K = 1000000;
bool RM[MAX_N + 1];
int PL1[MAX_K + 1];
int PV1[MAX_K + 1];
int PL2[MAX_K + 1];
int PV2[MAX_K + 1];
int PWS[MAX_N + 1];
int PWC;
int Ans;
vector<Edge> G[MAX_N + 1];

void solve(int r, int u, int p, int w, int d, int k) {
    if (w > k) return;
    if (PV1[w] != r) {
        PV1[w] = r;
        PL1[w] = d;
        PWS[PWC++] = w;
    } else if (PL1[w] > d) {
        PL1[w] = d;
    }
    if (PV2[k - w] == r) {
        if (Ans == -1 || Ans > PL2[k - w] + d) {
            Ans = PL2[k - w] + d;
        }
    }
    for (auto e: G[u]) {
        if (e.v == p || RM[e.v]) continue;
        solve(r, e.v, u, w + e.w, d + 1, k);
    }
}

void solve(int u, int k, CentroidDecomposition& sd) {
    PV1[0] = u;
    PL1[0] = 0;
    PV2[0] = u;
    PL2[0] = 0;
    PWC = 0;
    for (auto e: G[u]) {
        if (RM[e.v]) continue;
        solve(u, e.v, u, e.w, 1, k);
        for (int pwi = 0; pwi < PWC; ++pwi) {
            int w = PWS[pwi];
            int len = PL1[w];
            if (PV2[w] != u || PL2[w] > len) {
                PV2[w] = u;
                PL2[w] = len;
            }
        }
    }
    RM[u] = true;
    for (int v: sd.CentroidG()[u]) {
        solve(v, k, sd);
    }
}

int main() {
    int N, K;
    scanf("%d%d", &N, &K);
    CentroidDecomposition sd(N);
    for (int i = 0; i < N - 1; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back({v, w});
        G[v].push_back({u, w});
        sd.AddEdge(u, v);
    }
    sd.Solve();

    Ans = -1;
    memset(PV1, -1, sizeof(PV1));
    memset(PV2, -1, sizeof(PV2));
    solve(sd.Root(), K, sd);

    printf("%d\n", Ans);

    return 0;
}
