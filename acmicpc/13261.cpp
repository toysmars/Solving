// acmicpc 13261
// 
// divide and conqure optimization
// 분할정복을 이용한 dp 최적화

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

// Declearation of cost funciton.
// 1 <= a, b <= m
i64 cost(int a, int b);

// Solves dynamic programing with recurrence
//  dp[i][j] = min { dp[i-1][k] + C[k][j] } (0 <= k < j, 1 <= i <= n, 1 <= j <= m)
//  where C[a][b] is a monge array.
struct DivideAndConquerDPSolver {
    DivideAndConquerDPSolver(int n, int m): n(n), m(m), dpp(m+1), dpc(m+1) {}

    i64 Solve() {
        for (int j = 1; j <= m; ++j) {
            dpp[j] = cost(1, j);
        }
        for (int i = 1; i < n; ++i) {
            go(1, m, 1, m);
            dpp = dpc;
        }
        return dpp[m];
    }

    void go(int l, int r, int optl, int optr) {
        if (l > r) return;

        int mid = (l + r) / 2;
        pair<i64, int> best = { LLONG_MAX, -1 };

        for (int k = optl; k <= min(mid, optr); k++) {
            best = min(best, { dpp[k-1] + cost(k, mid), k });
        }

        dpc[mid] = best.first;
        int opt = best.second;

        go(l, mid - 1, optl, opt);
        go(mid + 1, r, opt, optr);
    }

    vector<i64> dpp;
    vector<i64> dpc;
    int n;
    int m;
};

int L, G;
i64 C[8001];
i64 S[8001];
i64 dp[8001][801];

i64 cost(int a, int b) {
    return (S[b] - S[a - 1]) * (b - a + 1);
}

// dp[i][j] be the min cost where i agents covers j prisoners.
//  = min { dp[i-1][k] + sum(k, j) * (j - k) } (0 <= k < j)
int main() {
    scanf("%d%d", &L, &G);
    for (int i = 1; i <= L; ++i) {
        scanf("%lld", &C[i]);
        S[i] = S[i-1] + C[i];
    }

    DivideAndConquerDPSolver dcdp(G, L);
    printf("%lld\n", dcdp.Solve());

    return 0;
}
