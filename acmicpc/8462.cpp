// square root decomposition
// mo's algorithm

#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

struct DistinctElementsQuery {
    int id;
    int l;
    int r;
};

struct DistinctElements {
    DistinctElements(const vector<i64>& arr, int maxN): v(arr), cnt(maxN + 1) {
        rt = max(1, (int)sqrt(v.size()));
    }

    vector<i64> solve(vector<DistinctElementsQuery>& qs) {
        vector<i64> ans(qs.size());
        auto cmp = [=](const DistinctElementsQuery &a, const DistinctElementsQuery &b) {
            int arb = a.r / rt;
            int brb = b.r / rt;
            return arb == brb ? a.l < b.l : arb < brb;
        };
        sort(qs.begin(), qs.end(), cmp);
        int i = 0;
        int j = 0;
        i64 sum = 0;
        for (auto& q: qs) {
            int l = q.l;
            int r = q.r;
            while (i < l) sum -= v[i] * (2 * cnt[v[i]] - 1), --cnt[v[i++]];
            while (i > l) cnt[v[--i]]++, sum += v[i] * (2 * cnt[v[i]] - 1);
            while (j < r) sum += v[j] * (2 * cnt[v[j]] + 1), cnt[v[j++]]++;
            while (j > r) --cnt[v[--j]], sum -= v[j] * (2 * cnt[v[j]] + 1);
            ans[q.id] = sum;
        }
        return ans;
    }

    vector<i64> v;
    vector<int> cnt;
    int rt;
};

int main() {
    int n, t;
    scanf("%d%d", &n, &t);
    vector<i64> arr(n + 1);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &arr[i]);
    }
    vector<DistinctElementsQuery> qs(t);
    for (int i = 0; i < t; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        qs[i] = { i, a, b + 1 };
    }
    DistinctElements de(arr, 1000001);
    auto res = de.solve(qs);
    for (auto r: res) {
        printf("%lld\n", r);
    }
    return 0;
}
