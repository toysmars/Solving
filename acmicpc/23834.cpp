// acmicpc 23834
//
// sliding window
// dynamic programing with deque

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

struct SlidingWindowMax {
    SlidingWindowMax(int window_size) : ws(window_size) {}

    pair<int, i64> Max(int ts) {
        while (!dq.empty()) {
            if (dq.front().first + ws > ts) break;
            dq.pop_front();
        }
        return dq.empty() ? make_pair(-1, 0ll) : dq.front();
    }

    void Add(int ts, i64 v) {
        while (!dq.empty()) {
            if (dq.back().second > v) break;
            dq.pop_back();
        }
        dq.emplace_back(ts, v);
    }

    int ws;
    deque<pair<int, i64>> dq;
};

int N, M;
i64 A[500010];
i64 B[500010];
i64 S[500010];
i64 dp[500010][2];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; ++i) scanf("%lld", &A[i]);
    for (int i = 1; i <= N; ++i) scanf("%lld", &B[i]);
    for (int i = 1; i <= N; ++i) S[i] = S[i-1] + A[i];

    SlidingWindowMax sw(M-1);
    sw.Add(0, 0);
    dp[0][0] = dp[0][1] = 0;
    i64 ans = 0;
    for (int i = 1; i <= N; ++i) {
        auto bmx = sw.Max(i-1);
        if (bmx.first == -1) {
            dp[i][0] = -1000000000;
        } else {
            dp[i][0] = bmx.second + S[i];
        }

        dp[i][1] = max(dp[i-1][0], dp[i-1][1]) - A[i];
        sw.Add(i, dp[i][1] - S[i]);

        ans = max(ans, dp[i][0]);
        if (i >= M) {
            ans = max(ans, dp[i-M][1] + S[i] - S[i-M] + B[i]);
        }
        //printf("%d - %lld %lld, %lld, %lld\n", i, bmx.second, dp[i][0], dp[i][1], ans);
    }
    printf("%lld\n", ans);

    return 0;
}
