// Knuth's Optimization
// 
// Example:
// * https://www.acmicpc.net/problem/13974

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef i64 val_t;

const int MAX_SIZE = 5000;
int dp[MAX_SIZE+1][MAX_SIZE+1];

// Knuth Optimization
// Applicable when:
// * C[a][c] + C[b][d] <= C[a][d] + C[b][c]
// * C[b][c] <= C[a][d]
// for:
// * DP[i][j] = min(i < k < j) { dp[i][k] + dp[k][j] } + C[i][j]
// * then range of k: K[i, j-1] <= K[i][j] <= K[i+1][j]
struct KnuthOpt {
    using CostFn = std::function<val_t(int, int)>;

    KnuthOpt(int size, CostFn costFn) : size(size), dp(size+1, vector<val_t>(size+1, 0)), mk(size+1, vector<val_t>(size+1, 0)), costFn(costFn) {}

    val_t Solve() {
        for (int i = 1; i <= size; ++i) {
            mk[i - 1][i] = i;
        }
        for (int w = 2; w <= size; ++w) {
            for (int i = 0; i + w <= size; ++i) {
                int j = i + w;
                dp[i][j] = numeric_limits<val_t>::max() / 2;
                for (int k = mk[i][j - 1]; k <= mk[i + 1][j]; ++k) {
                    val_t v = dp[i][k] + dp[k][j] + costFn(i, j - 1);
                    if (dp[i][j] > v) {
                        dp[i][j] = v;
                        mk[i][j] = k;
                    }
                }
            }
        }
        return dp[0][size];
    }

    int size;
    vector<vector<val_t>> dp; // dp[i][j] -> min of range [i+1, j]
    vector<vector<val_t>> mk;
    CostFn costFn;
};
