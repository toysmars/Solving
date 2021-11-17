// acmicpc 13548
//
// mo's algorithm
// square root decomposition
// most frequently appearing elements
// 가장 많이 등장하는 수

#include <bits/stdc++.h>
using namespace std;

struct MaxApperanceQuery {
    int id;
    int l;
    int r;
};

struct MaxApperance {
    MaxApperance(const vector<int>& arr, int maxN): v(arr), cnt(maxN + 1), acnt(maxN + 1) {
        rt = max(1, (int)sqrt(v.size()));
    }

    vector<int> solve(vector<MaxApperanceQuery>& qs) {
        vector<int> ans(qs.size());
        auto cmp = [=](const MaxApperanceQuery &a, const MaxApperanceQuery &b) {
            int arb = a.r / rt;
            int brb = b.r / rt;
            return arb == brb ? a.l < b.l : arb < brb;
        };
        sort(qs.begin(), qs.end(), cmp);
        int i = 0;
        int j = 0;
        maxA = 0;
        for (auto& q: qs) {
            int l = q.l;
            int r = q.r;
            while (j < r) insert(v[j++]);
            while (j > r) remove(v[--j]);
            while (i < l) remove(v[i++]);
            while (i > l) insert(v[--i]);
            ans[q.id] = maxA;
        }
        return ans;
    }

    vector<int> v;
    vector<int> cnt;
    vector<int> acnt;
    int rt;

private:
    int maxA;
    void insert(int x) {
        acnt[cnt[x]++]--;
        acnt[cnt[x]]++;
        maxA = max(maxA, cnt[x]);
    }
    void remove(int x) {
        maxA -= maxA == cnt[x] && acnt[cnt[x]] == 1;
        acnt[cnt[x]--]--;
        acnt[cnt[x]]++;
    }
};

int main() {
    int n, m;
    scanf("%d", &n);
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &m);
    vector<MaxApperanceQuery> qs(m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        qs[i] = { i, a, b + 1};
    }
    MaxApperance ma(arr, 100001);
    auto res = ma.solve(qs);
    for (auto r: res) {
        printf("%d\n", r);
    }
    return 0;
}
