// Divide and conquer optimization
// 분할정복을 이용한 dp 최적화
//
// Examples:
// https://www.acmicpc.net/problem/13261

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

// Declearation of cost funciton.
// 1 <= a, b <= m
i64 cost(int a, int b);

// Solves dynamic programing with recurrence
//  dp[i][j] = min { dp[i-1][k] + C[k][j] } (0 <= k < j, 1 <= i <= n, 1 <= j <= m)
//  where C[a][b] is a monge array.
// Time complexity
// * naive: O(nm^2)
// * dnc: O(nm log m)
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
