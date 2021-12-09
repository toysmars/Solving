// acmicpc 13974
//
// Knuth's optimization
// 크누스 최적화

#include <bits/stdc++.h>
using namespace std;

// Knuth Optimization
// Applicable when:
// * C[a][c] + C[b][d] <= C[a][d] + C[b][c]
// * C[b][c] <= C[a][d]
// for:
// * DP[i][j] = min(i < k < j) { dp[i][k] + dp[k][j] } + C[i][j]
// * then range of k: K[i, j-1] <= K[i][j] <= K[i+1][j]
const int MAX_SIZE = 5000;
const int MAX_INT = numeric_limits<int>::max();
int A[MAX_SIZE+1];
int S[MAX_SIZE+1];
int dp[MAX_SIZE+1][MAX_SIZE+1];
int mk[MAX_SIZE+1][MAX_SIZE+1];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
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
                dp[i][j] = MAX_INT;
                for (int k = mk[i][j - 1]; k <= mk[i + 1][j]; ++k) {
                    int v = dp[i][k] + dp[k][j] + S[j] - S[i];
                    if (dp[i][j] > v) {
                        dp[i][j] = v;
                        mk[i][j] = k;
                    }
                }
            }
        }
        printf("%d\n", dp[0][n]);
    }
    return 0;
}
