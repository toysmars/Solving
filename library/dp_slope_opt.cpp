// Dynamic Programing with Slope Optimization
// DP
// 함수개형을 이용한 최적화

// Examples:
// * https://www.acmicpc.net/problem/13323
// * https://www.acmicpc.net/problem/13324

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

// Slope Optimization
// https://codeforces.com/blog/entry/47821
// Applicable when:
// * DP[i][j] = min(k < j) { DP[i-1][k] } + | A[i] - j |
struct SlopeOptDPSolver {
    i64 Solve(vector<i64>& arr) {
        priority_queue<i64> pq;
        pq.push(arr[0]);
        i64 ans = 0;
        for (int i = 1; i < arr.size(); ++i) {
            auto a = arr[i];
            i64 optk = pq.top() + i;
            if (a <= optk) {
                ans += optk - a;
                pq.pop();
                pq.push(a - i);
            }
            pq.push(a - i);
        }
        return ans;
    }
};
