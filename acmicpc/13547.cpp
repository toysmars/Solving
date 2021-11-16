// acmicpc 13547
//
// square root decomposition
// mo's algorithm
// offline query
// number of distinct elements

#include <bits/stdc++.h>
using namespace std;

struct DistinctElementsQuery {
    int id;
    int l;
    int r;
};

struct DistinctElements {
    DistinctElements(const vector<int>& arr, int maxN): v(arr), cnt(maxN + 1) {
        rt = max(1, (int)sqrt(v.size()));
    }

    vector<int> solve(vector<DistinctElementsQuery>& qs) {
        vector<int> anss(qs.size());
        auto cmp = [=](const DistinctElementsQuery &a, const DistinctElementsQuery &b) {
            int arb = a.r / rt;
            int brb = b.r / rt;
            return arb == brb ? a.l < b.l : arb < brb;
        };
        sort(qs.begin(), qs.end(), cmp);
        int i = 0;
        int j = 0;
        int ans = 0;
        for (auto& q: qs) {
            int l = q.l;
            int r = q.r;
            while (i < l) ans -= --cnt[v[i++]] == 0;
            while (i > l) ans += cnt[v[--i]]++ == 0;
            while (j < r) ans += cnt[v[j++]]++ == 0;
            while (j > r) ans -= --cnt[v[--j]] == 0;
            anss[q.id] = ans;
        }
        return anss;
    }

    vector<int> v;
    vector<int> cnt;
    int rt;
};


int main() {
    int n, m;
    scanf("%d", &n);
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &m);
    vector<DistinctElementsQuery> qs(m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        qs[i] = { i, a, b + 1 };
    }
    DistinctElements de(arr, 1000001);
    auto res = de.solve(qs);
    for (auto r: res) {
        printf("%d\n", r);
    }
    return 0;
}
