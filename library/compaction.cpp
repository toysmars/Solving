// 좌표 압축
// 값 압축
//
// Examples:
// https://www.acmicpc.net/problem/11932
// https://www.acmicpc.net/problem/18870

#include <bits/stdc++.h>
using namespace std;

typedef int val_t;

vector<val_t> compaction(const vector<val_t>& arr) {
    int n = arr.size();
    vector<pair<val_t, int>> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = make_pair(arr[i], i);
    }
    sort(p.begin(), p.end());
    vector<val_t> ans(n);
    ans[p[0].second] = 0;
    for (int i = 1, j = 0; i < n; ++i) {
        j += p[i].first != p[i-1].first;
        ans[p[i].second] = j;
    }
    return ans;
}
