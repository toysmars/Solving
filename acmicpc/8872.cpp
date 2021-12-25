#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v, w;
};

const int MAX_N = 100000;
int N, M, L;
int W1[MAX_N + 1];
int W2[MAX_N + 1];
int W3[MAX_N + 1];
int W4[MAX_N + 1];
vector<Edge> g[MAX_N + 1];

int dfs1(int u) {
    if (W1[u] != -1) return -1000000001;
    W1[u] = 0;
    W2[u] = 0;
    for (auto e: g[u]) {
        int vw = dfs1(e.v);
        if (W1[u] <= vw + e.w) {
            W2[u] = W1[u];
            W1[u] = vw + e.w;
        } else if (W2[u] <= vw + e.w) {
            W2[u] = vw + e.w;
        }
    }
    //printf("dfs1 %d %d %d\n", u, W1[u], W2[u]);
    return W1[u];
}

int dfs2(int u, int pw) {
    if (W3[u] != -1) return 1000000001;
    int res = W3[u] = max(pw, W1[u]);
    W4[u] = max(pw + W1[u], W1[u] + W2[u]);
    //printf("dfs2 s %d %d %d %d %d %d\n", u, pw, W1[u], W2[u], W3[u], W4[u]);
    for (auto e: g[u]) {
        if (W1[e.v] + e.w == W1[u]) {
            res = min(res, dfs2(e.v, max(pw, W2[u]) + e.w));
        } else {
            res = min(res, dfs2(e.v, max(pw, W1[u]) + e.w));
        }
    }
    //printf("dfs2 e %d %d %d %d\n", u, pw, W3[u], res);
    return res;
}

int main() {
    scanf("%d%d%d", &N, &M, &L);
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    memset(W1, -1, sizeof(W1));
    memset(W2, 0, sizeof(W2));
    memset(W3, -1, sizeof(W3));
    for (int u = 0; u < N; ++u) {
        if (W1[u] == -1) {
            dfs1(u);
        }
    }
    vector<int> cs;
    for (int u = 0; u < N; ++u) {
        if (W3[u] == -1) {
            cs.push_back(dfs2(u, 0));
            //printf("%d %d\n", u, cs[cs.size()-1]);
        }
    }
    int ans = 0;
    for (int u = 0; u < N; ++u) {
        ans = max(ans, W4[u]);
    }
    if (cs.size() == 1) {
        ans = max(ans, cs[0]);
    } else {
        sort(cs.rbegin(), cs.rend());
        ans = max(ans, cs[0] + cs[1] + L);
        if (cs.size() >= 3) {
            ans = max(ans, cs[1] + cs[2] + 2 * L);
        }
    }
    printf("%d\n", ans);
    return 0;
}
