// maximum value in sliding window
// 
// Examples:
// * https://www.acmicpc.net/problem/23834

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
