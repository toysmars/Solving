// acmicpc 13974
//
// Knuth's optimization
// 크누스 최적화

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

// Knuth Optimization
// Applicable when:
// * C[a][c] + C[b][d] <= C[a][d] + C[b][c]
// * C[b][c] <= C[a][d]
// for:
// * DP[i][j] = min(i < k < j) { dp[i][k] + dp[k][j] } + C[i][j]
// * then range of k: K[i, j-1] <= K[i][j] <= K[i+1][j]
const int MAX_SIZE = 5000;
i64 dp[MAX_SIZE+1][MAX_SIZE+1];
i64 mk[MAX_SIZE+1][MAX_SIZE+1];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        vector<int> A(n);
        vector<i64> S(n + 1);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &A[i]);
            S[i + 1] = S[i] + A[i];
        }
        for (int i = 1; i <= n; ++i) {
            mk[i - 1][i] = i;
        }
        for (int w = 2; w <= n; ++w) {
            for (int i = 0; i + w <= n; ++i) {
                int j = i + w;
                dp[i][j] = numeric_limits<i64>::max() / 2;
                for (int k = mk[i][j - 1]; k <= mk[i + 1][j]; ++k) {
                    i64 v = dp[i][k] + dp[k][j] + S[j] - S[i];
                    if (dp[i][j] > v) {
                        dp[i][j] = v;
                        mk[i][j] = k;
                    }
                }
            }
        }
        printf("%lld\n", dp[0][n]);
    }
    return 0;
}
