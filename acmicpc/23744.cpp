// acmicpc 23744
//
// segment tree
// sweeping

#include <bits/stdc++.h>
using namespace std;

typedef int val_t;
const val_t DEFAULT = 0;

struct SegmentTree {
    SegmentTree(int n, val_t (*op)(val_t, val_t)) : n(n), t(4 * n + 1, DEFAULT), op(op) {}

    void update(int i, val_t x) {
        update(i, x, 1, 1, n + 1);
    }
    val_t update(int i, val_t x, int idx, int l, int r) {
        if (l > i || r <= i || l >= r) {
            return t[idx];
        }
        int len = r - l;
        if (len == 1) {
            t[idx] = x;
            return t[idx];
        }
        val_t res1 = update(i, x, idx * 2 + 0, l, l + len / 2);
        val_t res2 = update(i, x, idx * 2 + 1, l + len / 2, r);
        t[idx] = op(res1, res2);
        return t[idx];
    }
    val_t query(int ql, int qr) {
        return query(ql, qr, 1, 1, n + 1);
    }
    val_t query(int ql, int qr, int idx, int l, int r) {
        if (l >= qr || r <= ql || l >= r) {
            return DEFAULT;
        }
        if (ql <= l && qr >= r) {
            return t[idx];
        }
        int len = r - l;
        val_t res1 = query(ql, qr, idx * 2 + 0, l, l + len / 2);
        val_t res2 = query(ql, qr, idx * 2 + 1, l + len / 2, r);
        return op(res1, res2);
    }

    static val_t min(val_t a, val_t b) { return a < b ? a : b; }
    static val_t max(val_t a, val_t b) { return a > b ? a : b; }

    int n;
    vector<val_t> t;
    val_t (*op)(val_t, val_t);
};

int maxop(int a, int b) { return a > b ? a : b; }

int main() {
    int n;
    scanf("%d", &n);
    vector<int> rs(n + 1);
    vector<pair<int, int>> ds(n+1);
    vector<pair<pair<int, int>, int>> st;
    for (int i = 1; i <= n; ++i) {
        int a, l, r;
        scanf("%d%d%d", &a, &l, &r);
        rs[i] = a;
        ds[i] = make_pair(l, r);
        st.emplace_back(make_pair(i - r, i - l), i);
        st.emplace_back(make_pair(i + l, i + r), i);
    }
    sort(st.begin(), st.end());
    priority_queue<pair<int, int>> pq;
    int j = 0;
    int ans = -1;
    SegmentTree stree(n + 1, maxop);
    for (int i = 1; i <= n; ++i) {
        while (j < st.size() && st[j].first.first <= i) {
            pq.push(make_pair(-st[j].first.second, st[j].second));
            stree.update(st[j].second, rs[st[j].second]);
            //printf(" + %d - %d (%d~%d)\n", i, st[j].second, st[j].first.first, st[j].first.second);
            j += 1;
        }
        while (!pq.empty()) {
            auto t = pq.top();
            if (-t.first >= i) break;
            pq.pop();
            stree.update(t.second, 0);
            //printf(" - %d - %d -> %d\n", i, t.second, stree.query(1, 4));
        }
        ans = max(ans, stree.query(max(1, i - ds[i].second), max(1, i - ds[i].first + 1)) - rs[i]);
        ans = max(ans, stree.query(min(n + 1, i + ds[i].first), min(n + 1, i + ds[i].second + 1)) - rs[i]);
    }
    printf("%d\n", ans);
    return 0;
}
